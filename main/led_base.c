#include "led_base.h"

void gpio_conf(int *pin) {
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << (*pin),
        .pull_down_en = 0,
        .pull_up_en = 0
    };
    esp_err_t ret = gpio_config(&io_conf);
    if(ret != ESP_OK) {
        printf("Error: %s\n", esp_err_to_name(ret));
    }
}

void ledc_timer_conf(int *freq, int *timer) {
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = *freq,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = (*timer)
    };
    esp_err_t ret = ledc_timer_config(&ledc_timer);
}

void ledc_channel_conf(int *pin,int *channel,int *ledc_timer) {
    ledc_channel_config_t ledc_channel = {
        .channel = (*channel),
        .duty = 0,
        .gpio_num = (*pin),
        .intr_type = LEDC_INTR_DISABLE,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_sel = (*ledc_timer)
    };
    esp_err_t ret = ledc_channel_config(&ledc_channel);
}

void breathe(int *ledc_channel) {
    for(int i = 0; i < 1023; i++) {
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, (*ledc_channel), i);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, (*ledc_channel));
        printf("Duty: %d\n", i);
        
    }
    for(int i = 1023; i > 0; i--) {
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, (*ledc_channel), i);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, (*ledc_channel));
        printf("Duty: %d\n", i);
        
    }
}

//the intesinty parameter depends on your duty resoultion I.E 10 bit mode goes from 0(0%) - 1024(100%)
void turn_on_led_at_bright(int *ledc_channel ,int intensity)
{
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, (*ledc_channel), intensity);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, (*ledc_channel));
}