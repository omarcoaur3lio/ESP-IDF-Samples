## Escaneamento de redes Wi-Fi

> :bulb: Este é um exemplo básico de como utilizar o framework ESP-IDF para realizar o escaneamento de redes Wi-Fi com um ESP32.

<br>


**✅ Com ele é possível:**

- Escanear as redes Wi-Fi disponíveis
- Guardar o resultado em uma [partição NVS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/nvs_flash.html?highlight=nvs_flash_init#nvs-partition-generator-utility)
- Listar os seguintes atributos das redes encontradas:
      - SSID
      - RSSI
      - MAC Address

### Funções utilizadas
Listei abaixo algumas das funções utilizadas no exemplo, cada uma com uma breve descrição de sua funcionalidade :wink:.

Todo o processo de escaneamento é realizado pelo método `wifi_scan()`, sendo realizado antes de sua chamada, uma verificação do estado da memória não volátil do ESP.

``` C
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
``` 

O método `nvs_flash_init()` é o responsável por inicializar e possibilitar o uso da memória, assim, verfica-se se existe espaço disponível, caso não exista, o método `nvs_flash_erase()` apaga o conteúdo existente, liberando espaço.

<br>

**Métodos utilizados pela função *wifi_scan***

- `esp_netif_init`: Inicializa a pilha TCP
- `esp_netif_create_default_wifi_sta`: Configura o ESP para atuar no [modo *station*](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_netif.html?highlight=esp_netif_create_default_wifi_sta#wifi-default-api-reference)
- `esp_wifi_scan_start`: Realiza a varredura das redes Wi-Fi
- `esp_wifi_scan_get_ap_records`: Grava na memória as redes encontradas
