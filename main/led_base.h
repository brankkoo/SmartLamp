#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h> 
#include <driver/ledc.h>
#define LEDC_CHANNEL_0 0  
#define LEDC_TIMER_0 0
#define LEDC_HIGH_SPEED_MODE 0
#define LEDC_INTR_DISABLE 0
#define LEDC_TIMER_10_BIT 10

void gpio_conf(int *pin);
void ledc_timer_conf(int *freq, int *ledc_timer); 
void ledc_channel_conf(int *pin,int *ledc_channel,int *ledc_timer);
void breathe(int *ledc_channel);
void turn_on_led_at_bright(int *ledc_channel ,int intensity);