#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_log.h"

#define SSID                "Meu SSID"
#define PASS                "Minha Senha"
#define TENTATIVAS    5

static const char *IP = "Device IP";

static EventGroupHandle_t grupoDeEventos;  // Para utilização do FreeRTOS

// Esses estados serão alterados pelo gerador de eventos
#define WIFI_CONNECTED_BIT      BIT0
#define WIFI_FAIL_BIT                      BIT1

static int tentativa = 0;

static void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (tentativa < TENTATIVAS) {
            esp_wifi_connect();
            tentativa++;
            printf("Tentando conectar ao AP...\n");
        } else {
            xEventGroupSetBits(grupoDeEventos, WIFI_FAIL_BIT);
        }
        printf(":( Não foi possível conectar-se ao AP.\n");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {

        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(IP, IPSTR, IP2STR(&event->ip_info.ip));
        tentativa = 0;
        xEventGroupSetBits(grupoDeEventos, WIFI_CONNECTED_BIT);

    }
}

void wifi_init(void) {
    
    grupoDeEventos = xEventGroupCreate(); 

    ESP_ERROR_CHECK(esp_netif_init()); // Inicializa pilha TCP

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    // Configuração do ESP para operar como "station"
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&config));

    esp_event_handler_instance_t ip_qualquer;
    esp_event_handler_instance_t ip_obtido;

    ESP_ERROR_CHECK( esp_event_handler_instance_register(
                                                WIFI_EVENT,
                                                ESP_EVENT_ANY_ID,
                                                &event_handler,
                                                NULL,
                                                &ip_qualquer
    ) );

    ESP_ERROR_CHECK( esp_event_handler_instance_register(
                                                IP_EVENT,
                                                IP_EVENT_STA_GOT_IP,
                                                &event_handler,
                                                NULL,
                                                &ip_obtido
    ) );

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = SSID,
            .password = PASS,
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,

            // Para redes com RSN
            .pmf_cfg = {
                .capable = true,
                .required = false
            },
        }
    };
    // Configura e inicializa a Wi-FI
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    // Aguarda até se conectar ou retorna uma falha caso não consiga
    EventBits_t bits = xEventGroupWaitBits(
        grupoDeEventos,
        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
        pdFALSE,
        pdFALSE,
        portMAX_DELAY
    );

    // Verifica se conseguiu se conectar
    if ( bits & WIFI_CONNECTED_BIT ) {
        printf("Conectado a rede %s\n", SSID);
    } else if ( bits & WIFI_CONNECTED_BIT ) {
        printf(":( Falha ao conectar-se com a rede %s\n", SSID);
    } else {
        printf(":( Algo deu errado... Tente novamente.\n");
    }

    wifi_ap_record_t conexao;
    esp_wifi_sta_get_ap_info(&conexao);
    printf("RSSI: %d\n", conexao.rssi);

    // Descarta o evento e seu grupo
    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, ip_obtido));
    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, ip_qualquer));
    vEventGroupDelete(grupoDeEventos);

}

void app_main(void) {
    //Inicialização da partição NVS
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    
    wifi_init();

}
