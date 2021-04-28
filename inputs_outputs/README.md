## Entradas e saídas do ESP

> Este é um exemplo básico de como utilizar o framework ESP-IDF para leitura e acionamento de entradas e saídas.

**Com ele é possível realizar:**

- Leitura de uma entrada digital
- Acionamento de uma saída digital

### Circuito utilizado no exemplo

<p align="center">
   <img src="../.github/esp32_proto.png" alt="Esquemático" width="70%"/>  
</p>

**Componentes utilizados:**

- [ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html)
- Led RGB
- Push Button
- Resistor 10K


{:note:}

**Note:** Owners and administrators can add outside collaborators to a repository.

{:endnote:}

**Conexões:**

| Componente       | Pino do ESP |
| -----------------| ----------- |
| Push Button      | 34          |
| Led              | 33          | 
