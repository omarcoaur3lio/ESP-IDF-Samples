## Entradas e saídas do ESP

> :bulb: Este é um exemplo básico de como utilizar o framework ESP-IDF para leitura e acionamento de entradas e saídas.

<br>

**Com ele é possível realizar:**

- Leitura de uma entrada digital
- Acionamento de uma saída digital

<br>

### Circuito utilizado no exemplo

<p align="center">
   <img src="../.github/esp32_proto.png" alt="Esquemático" width="70%"/>  
</p>

**Componentes utilizados:**

- [ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html)
- Led RGB
- Push Button
- Resistor 10K

<br>

:vertical_traffic_light: Atenção
```
No circuito usado como exemplo, foi utilizado um Led RGB, 
porém nada impede o uso de um Led convencional.
```
<br>

**Conexões:**

| Componente       | Pino do ESP |
| -----------------| ----------- |
| Push Button      | 34          |
| Led              | 33          | 
