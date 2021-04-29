## Conexão em rede Wi-Fi

> :bulb: Este é um exemplo básico de como utilizar o framework ESP-IDF para conectar-se a uma rede Wi-Fi com um ESP32.

<br>


**✅ Com ele é possível:**

- Conectar a um rede Wi-Fi
- Imprimir o IP obtido
- Imprimir o nível de sinal (RSSI)

<br>

> <br> Neste exemplo, assume-se que o usuário já possui o nome e a senha da rede em que pretende se conectar :wink:<br>. 

Essas informações devem ser preenchidas nas constantes `SSID` e `PASS`.

<br>

**Métodos utilizados para conexão e configuração**

- `wifi_init`: Responsável por inicializar e configurar a Wi-Fi
- `xEventGroupCreate`: Criação de um grupo de eventos a serem registrados no loop
- `event_handler`: Responsável pelo tratamento dos eventos registrados
