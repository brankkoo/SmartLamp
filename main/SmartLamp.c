#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_base.h"
#include "driver/ledc.h"
#include <esp_adc/adc_continuous.h>
#include "driver/adc.h"
#include "esp_log.h"  
#include "esp_adc_cal.h"  
void app_main(void)
{    
 int pins[3] = {GPIO_NUM_16,GPIO_NUM_17,GPIO_NUM_18};
 int channels[3] = {LEDC_CHANNEL_0,LEDC_CHANNEL_1,LEDC_CHANNEL_2};
 int ledc_timer_freq = 1000;
 int timers[1] = {LEDC_TIMER_0};

//adc1_6
static esp_adc_cal_characteristics_t adc1_chars;
esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);


adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_11);
adc1_config_width(ADC_WIDTH_BIT_12);    

//green
gpio_conf(&pins[0]);
ledc_timer_conf(&ledc_timer_freq,&timers[0]);
ledc_channel_conf(&pins[0],&channels[0],&timers[0]);

//red
gpio_conf(&pins[1]);
ledc_timer_conf(&ledc_timer_freq,&timers[0]);
ledc_channel_conf(&pins[1],&channels[1],&timers[0]);

//blue
gpio_conf(&pins[2]);
ledc_timer_conf(&ledc_timer_freq,&timers[0]);
ledc_channel_conf(&pins[2],&channels[2],&timers[0]);
static const char *TAG = "ADC"; 
gpio_set_direction(GPIO_NUM_33,GPIO_MODE_INPUT);
int inte;
    while(1) {
    int volt = adc1_get_raw(ADC1_CHANNEL_4);
    //float volt2 = volt*(3.3/4096);
    printf("adc : %i \n",volt);  
    
    // if(volt > 385){
    //     inte = 512;
    // }
    // else{
    //     inte = 0;
    // }

     turn_on_led_at_bright(&channels[0],volt);
     turn_on_led_at_bright(&channels[1],volt);
      vTaskDelay(10 / portTICK_PERIOD_MS);
    // turn_on_led_at_bright(&channels[2],inte);
       }
}
