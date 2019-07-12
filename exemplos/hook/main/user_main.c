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

//não funcionou, deveria ter substituido a função weak declarada pelo ESP-IDF, mas não dá certo
// void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName ){
//     printf("%s overflowed the stack", pcTaskName);
// };


#define BOOT_BTN 0
#define LEDCOMMON 15
#define STACK_SIZE 1024


long long idle_ticks=0;
long long fail_ticks=0;
long long tick_ticks=0;


void vApplicationIdleHook( void ){
    idle_ticks++;
};

void vApplicationTickHook( void ){
    tick_ticks++;
};

void vApplicationMallocFailedHook( void ){
    fail_ticks++;
};


float crazyrecursion(float x){
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    //não tem função alguma
    for(int i=10;i>0;i--) x += a[i]/x;
    
    return x+crazyrecursion(x-1)-crazyrecursion(x-1);
}

void vStackBuster(){
    crazyrecursion(20);
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



  while(1){
  //     xReturned = xTaskCreate(vStackBuster, "Task button",  1024, NULL, configMAX_PRIORITIES - 1, &led_toggler);
        int malloc_error = malloc(30000);//muitos bytes,vai falhar
        
        //xTaskCreate(vStackBuster,"stackbuster",1024,NULL,1,NULL); 

        printf("idle: %ld,\tfail:  %ld,\tticks:  %ld, ", (long int)idle_ticks, (long int)fail_ticks, (long int)tick_ticks);
        printf((!malloc_error)?"deu erro no malloc\n":"malloc funcionou\n");
        vTaskDelay(5000 / portTICK_RATE_MS);
  };
  
}

