#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"

#define LED (25)

#define LEDC_TEST_DUTY             (6000) // Define a intensidade do LEd
#define LEDC_TEST_FADE_TIME   (1000)

void app_main() {

    // Estrutura de configuração do timer
    ledc_timer_config_t timerParaLED = {
        .duty_resolution  = LEDC_TIMER_13_BIT,    // resolution of PWM duty
        .freq_hz                  = 5000,                               // frequency of PWM signal
        .clk_cfg                   = LEDC_AUTO_CLK,          // Auto select the source clock
        .speed_mode        = LEDC_HIGH_SPEED_MODE
    };
    // Pode-se adicionar valores à propriedades diretamente
    timerParaLED.timer_num = LEDC_TIMER_0;

    ledc_timer_config(&timerParaLED);

    // Estrutura para configurar o canal
    ledc_channel_config_t canalParaLED = {
        .channel             = LEDC_CHANNEL_0,
        .duty                    = 0,
        .gpio_num          = LED,
        .speed_mode    = LEDC_HIGH_SPEED_MODE,
        .hpoint                = 0,
        .timer_sel           = LEDC_TIMER_0
    };
    ledc_channel_config(&canalParaLED);

    ledc_fade_func_install(0);

    while (true) {

        /* Blink com duty */
        for (int i = 0; i <=4; i++) {
            ledc_set_duty(canalParaLED.speed_mode, canalParaLED.channel, LEDC_TEST_DUTY);
            ledc_update_duty(canalParaLED.speed_mode, canalParaLED.channel);

            vTaskDelay(100 / portTICK_PERIOD_MS);

            ledc_set_duty(canalParaLED.speed_mode, canalParaLED.channel, 0);
            ledc_update_duty(canalParaLED.speed_mode, canalParaLED.channel);
            
            vTaskDelay(100 / portTICK_PERIOD_MS);

        }
        vTaskDelay(500 / portTICK_PERIOD_MS);

        /* Blink com função fade */
        ledc_set_fade_with_time(canalParaLED.speed_mode, canalParaLED.channel, LEDC_TEST_DUTY, LEDC_TEST_FADE_TIME);
        ledc_fade_start(canalParaLED.speed_mode, canalParaLED.channel, LEDC_FADE_NO_WAIT);

        vTaskDelay(800 / portTICK_PERIOD_MS);

        ledc_set_fade_with_time(canalParaLED.speed_mode, canalParaLED.channel, 0, LEDC_TEST_FADE_TIME);
        ledc_fade_start(canalParaLED.speed_mode, canalParaLED.channel, LEDC_FADE_NO_WAIT);

        vTaskDelay(1000 / portTICK_PERIOD_MS);

    }
}