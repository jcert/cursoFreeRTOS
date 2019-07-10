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
#include "freertos/queue.h"
#include "freertos/task.h"

#include "tasks.h"

//void __attribute__((weak)) xTask1(){};
//void __attribute__((weak)) xTask2(){};
QueueHandle_t message_queue;

#define BOOT_BTN 0
#define LEDCOMMON 15
#define STACK_SIZE 1024



void vGenerate10(){
  const int a = 10;
  while(1){
    xQueueSend(message_queue,&a,1);
    vTaskDelay(10000 / portTICK_RATE_MS);
  }
}

void vGenerate11(){
  const int a = 11;
  while(1){
    xQueueSend(message_queue,&a,1);
    vTaskDelay(11000 / portTICK_RATE_MS);
  }
}

void vGenerate20(){
  const int a = 20;
  while(1){
    xQueueSend(message_queue,&a,1);
    vTaskDelay(20000 / portTICK_RATE_MS);
  }
}


void vConsume12(){
  int a = 0;
  while(1){
    if( pdTRUE == xQueueReceive(message_queue,&a,1) ){
      printf("C12:\t%d\n",a);
    }else{
      printf("C12:\tNone\n");
      }
    vTaskDelay(12000 / portTICK_RATE_MS);
  }
}


void vConsume6(){
  int a = 0;
  while(1){
    if( pdTRUE == xQueueReceive(message_queue,&a,1) ){
      printf("C6:\t%d\n",a);
    }else{
      printf("C6:\tNone\n");
      }
    vTaskDelay(6000 / portTICK_RATE_MS);
  }
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


  message_queue = xQueueCreate(100, sizeof(int));

  xReturned = xTaskCreate(vGenerate10, "Task button",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1, NULL);
  xReturned = xTaskCreate(vGenerate11, "Task button",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1, NULL);
  xReturned = xTaskCreate(vGenerate20, "Task button",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1, NULL);
  xReturned = xTaskCreate(vConsume12, "Task button",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1, NULL);
  xReturned = xTaskCreate(vConsume6, "Task button",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1,NULL);

  while(1){
        vTaskDelay(1000 / portTICK_RATE_MS);
        printf("Mensagens na fila: %ld\n",uxQueueMessagesWaiting(message_queue));
  };
  
}

