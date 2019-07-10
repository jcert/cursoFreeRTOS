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
#include "freertos/stream_buffer.h"
#include "freertos/task.h"

#include "math.h"
#include "tasks.h"

//void __attribute__((weak)) xTask1(){};
//void __attribute__((weak)) xTask2(){};

StreamBufferHandle_t xMessageStream;

#define BOOT_BTN 0
#define LEDCOMMON 15
#define STACK_SIZE 1024


void vGenerate(){
  char aux[]="HS Maringa :)\0";
  while(1){
    int n = rand() % 10;
    if(n<2){
      //se não conseguir mandar toda a mensagem, a parte não enviada é perdida
      xStreamBufferSend( xMessageStream,aux,14,2);
    }else{
      for(int k=0;k<n;k++){
        char x = 'A'+rand()%25;
        xStreamBufferSend( xMessageStream,&x,1,2);
      }
    }
    vTaskDelay(300 / portTICK_RATE_MS);
  }
}


void vConsume(){
  char aux[30];
  int n,linebreak=80;
  while(1){
    n = xStreamBufferReceive( xMessageStream,aux,30,portMAX_DELAY);
    for(int i=0;i<n;i++){
      linebreak--;
      if(linebreak<1){
        linebreak=80;
        printf("\n");
        }
      printf("%c",aux[i]);
      }
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


  xMessageStream = xStreamBufferCreate(100,25);

  xReturned = xTaskCreate(vGenerate, "Task button",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1, NULL);
  xReturned = xTaskCreate(vConsume, "Task button",  STACK_SIZE, NULL, configMAX_PRIORITIES - 1,NULL);

  while(1){
        vTaskDelay(1000 / portTICK_RATE_MS);
  };
  
}

