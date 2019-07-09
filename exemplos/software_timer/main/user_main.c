/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>

#include "esp_system.h"
#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "freertos/task.h"

#include "tasks.h"

//void __attribute__((weak)) xTask1(){};
//void __attribute__((weak)) xTask2(){};

TimerHandle_t tOneShot, tAutoReload;

#define BOOT_BTN 0
#define LEDCOMMON 15
#define STACK_SIZE 1024


void vTaskButton(){

  while(1){
  
    if(!gpio_get_level(LED1) && !gpio_get_level(BOOT_BTN)){
      xTimerStart(tOneShot, 1);
      gpio_set_level(LED1,1);
    }
  
    vTaskDelay(100 / portTICK_RATE_MS);
  }

}

void vLED1(){
  gpio_set_level(LED1,0);

}

void vLED2(){
  gpio_set_level(LED2,!gpio_get_level(LED2));

}


/******************************************************************************
 * FunctionName : app_main
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void app_main(void)
{
  gpio_config_t io_conf;
  BaseType_t xReturned;
  printf("SDK version:%s\n", esp_get_idf_version());

  //disable interrupt
  io_conf.intr_type = GPIO_INTR_DISABLE;
  //set as output mode
  io_conf.mode = GPIO_MODE_OUTPUT;
  //bit mask of the pins that you want to set,e.g.GPIO15/16
  io_conf.pin_bit_mask  = 1ULL<<LED1; 
  io_conf.pin_bit_mask |= 1ULL<<LED2;
  io_conf.pin_bit_mask |= 1ULL<<LED3;
  io_conf.pin_bit_mask |= 1ULL<<LEDCOMMON;
  //disable pull-down mode
  io_conf.pull_down_en = 0;
  //disable pull-up mode
  io_conf.pull_up_en = 0;
  //configure GPIO with the given settings
  gpio_config(&io_conf);
  
  gpio_set_level(LED1,0);
  gpio_set_level(LED2,0);
  gpio_set_level(LED3,0);
  gpio_set_level(LEDCOMMON,0);
  printf("inicio\n");

  //timer auto-reload 1s
  //
  //task botão 
  //
  //timer one-shot 5s turns
  //
  tOneShot = xTimerCreate("oneshot", 5000 / portTICK_RATE_MS,pdFALSE, (void *) 0, vLED1 );
  tAutoReload =  xTimerCreate("autoreload", 1000 / portTICK_RATE_MS,pdTRUE, (void *) 0, vLED2);
  xTimerStart(tAutoReload, 1);

  xReturned = xTaskCreate(vTaskButton, "Task button",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1,NULL);


  while(1){
        vTaskDelay(1000 / portTICK_RATE_MS);
  };
  
}

