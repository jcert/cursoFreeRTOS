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
#include "freertos/task.h"

#include "tasks.h"

//void __attribute__((weak)) xTask1(){};
//void __attribute__((weak)) xTask2(){};

SemaphoreHandle_t xSemaphoreBinary;


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
  xSemaphoreBinary = xSemaphoreCreateBinary();

  //se ele não criou o semáforo, fica travado nisto 
  while(xSemaphoreBinary == NULL){
        vTaskDelay(1000 / portTICK_RATE_MS);
  };
  xSemaphoreGive( xSemaphoreBinary );

  //disable interrupt
  io_conf.intr_type = GPIO_INTR_DISABLE;
  //set as output mode
  io_conf.mode = GPIO_MODE_OUTPUT;
  //bit mask of the pins that you want to set,e.g.GPIO15/16
  io_conf.pin_bit_mask  = 1ULL<<LED1; 
  io_conf.pin_bit_mask |= 1ULL<<LED2;
  //disable pull-down mode
  io_conf.pull_down_en = 0;
  //disable pull-up mode
  io_conf.pull_up_en = 0;
  //configure GPIO with the given settings
  gpio_config(&io_conf);
  
  printf("inicio\n");

  xReturned = xTaskCreate(xTask1, "Task1",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1,NULL);
  xReturned = xTaskCreate(xTask2, "Task2",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1,NULL); 


  while(1){
        //printf("free semaphores: %ld",uxSemaphoreGetCount(xSemaphoreCounting));
        vTaskDelay(1000 / portTICK_RATE_MS);
  };
  
}

