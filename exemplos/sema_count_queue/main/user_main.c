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
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "tasks.h"

//void __attribute__((weak)) xTask_period1(){};
//void __attribute__((weak)) xTask_period2(){};
//void __attribute__((weak)) xTask_period4(){};
//void __attribute__((weak)) xTask_period8(){};
//void __attribute__((weak)) xTask_period16(){};

SemaphoreHandle_t xSemaphoreCounting;
QueueHandle_t xQueuePinosLED;
uint8_t led_list[3] = {12,13,15};


#define STACK_SIZE 1024

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
  xSemaphoreCounting = xSemaphoreCreateCounting(2, 2);

  //se ele não criou o semáforo, fica travado nisto 
  while(xSemaphoreCounting == NULL){
        vTaskDelay(1000 / portTICK_RATE_MS);
  };


  //disable interrupt
  io_conf.intr_type = GPIO_INTR_DISABLE;
  //set as output mode
  io_conf.mode = GPIO_MODE_OUTPUT;
  //bit mask of the pins that you want to set,e.g.GPIO15/16
  io_conf.pin_bit_mask  = 1ULL<<led_list[0]; 
  io_conf.pin_bit_mask |= 1ULL<<led_list[1];
  io_conf.pin_bit_mask |= 1ULL<<led_list[2];
  printf("%x",io_conf.pin_bit_mask);
  //disable pull-down mode
  io_conf.pull_down_en = 0;
  //disable pull-up mode
  io_conf.pull_up_en = 0;
  //configure GPIO with the given settings
  gpio_config(&io_conf);
  
  xQueuePinosLED = xQueueCreate(3, sizeof(uint8_t) );
  //se ele não criou a fila, fica travado nisto 
  while(xQueuePinosLED == NULL){
        vTaskDelay(1000 / portTICK_RATE_MS);
  };
  xQueueSend(xQueuePinosLED,&led_list[0],1);
  xQueueSend(xQueuePinosLED,&led_list[1],1);
  xQueueSend(xQueuePinosLED,&led_list[2],1);

  printf("inicio\n");

  xReturned = xTaskCreate(xTask_period1, "TaskPeriod1",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1,NULL);
  xReturned = xTaskCreate(xTask_period2, "TaskPeriod2",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1,NULL);      
  xReturned = xTaskCreate(xTask_period4, "TaskPeriod4",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1,NULL);      
  xReturned = xTaskCreate(xTask_period8, "TaskPeriod8",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1,NULL);         
  xReturned = xTaskCreate(xTask_period16,"TaskPeriod16", STACK_SIZE, NULL, configMAX_PRIORITIES - 1,NULL);         


  while(1){
        //printf("free semaphores: %ld",uxSemaphoreGetCount(xSemaphoreCounting));
        vTaskDelay(1000 / portTICK_RATE_MS);
  };
  
}

