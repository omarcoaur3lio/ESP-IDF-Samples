#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"


#define LED 33 // Led conectado ao pino D33
#define BTN 34 // Botão conectado ao pino D34

void app_main(void){
	
	gpio_set_direction(LED, GPIO_MODE_OUTPUT); // Define o pino como saída
	gpio_set_direction(BTN, GPIO_MODE_INPUT); // Define o pino como entrada

	while(1) {

	  while (!gpio_get_level( BTN )) {
			gpio_set_level(LED, 0); // Define o nível do pino
	  }
		gpio_set_level(LED, 1);
  }
}