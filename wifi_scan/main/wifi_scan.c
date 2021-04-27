#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

#include "esp_log.h"

static void wifi_scan(void) {

    ESP_ERROR_CHECK(esp_netif_init()); // Inicializa a pilha TCP
    
    // ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta(); // Configura o ESP para o modo "station"
    assert(sta_netif); // Verifica se a wifi foi corretamente configurada como STA

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); // Configura a wi-fi para os valores padrão
    ESP_ERROR_CHECK(esp_wifi_init(&cfg)); // Inicializa a wi-fi

    uint16_t  numberForList = 10; // Número máx de redes a serem listadas

    wifi_ap_record_t redes_encontradas[10]; // Array para armazenas as redes escaneadas

    uint16_t numeroRedesEncontradas = 0;

    memset(redes_encontradas, 0, sizeof(redes_encontradas)); // Jeito fresco de preencher o array com zeros;

    // Inicializa a wi-fi com o modo de configuração "station"
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));  
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, true)); // Inicia a varredura sem uma configuração inicial
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&numberForList, redes_encontradas)); // Preenche o array com as redes encontradas
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&numeroRedesEncontradas));

    printf("\n");
    printf("Foram encontradas %d redes\n", numeroRedesEncontradas);
    printf("*-------------------------------------------------*\n");

    printf("     SSID    | Channel | RSSI |       MAC  \n");            

    for (int i = 0; (i < numberForList); i++) {
        printf(
            "%12s | %7d | %4d |  %2x:%2x:%2x:%2x:%2x:%2x \n",
            redes_encontradas[i].ssid, 
            redes_encontradas[i].primary, 
            redes_encontradas[i].rssi , 
            *redes_encontradas[i].bssid, 
            *(redes_encontradas[i].bssid+1), 
            *(redes_encontradas[i].bssid+2), 
            *(redes_encontradas[i].bssid+3), 
            *(redes_encontradas[i].bssid+4), 
            *(redes_encontradas[i].bssid+5)
        );
    }
}

void app_main(void) {

    esp_err_t ret = nvs_flash_init();

    // verifica se a memoria está cheia ou com dados que impedem uma novainicialização
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // Apaga os dados 
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

        wifi_scan();
}