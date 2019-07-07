#include <stdio.h>

#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "tasks.h"

extern SemaphoreHandle_t xSemaphoreBinary;

#define USE_SEMA_BIN

#ifndef USE_SEMA_BIN
void xTask1(void *pvParameters){
  while(1){
      printf("t=1 LED=%d\n",LED1);
      gpio_set_level(LED1,1);
      vTaskDelay(500 / portTICK_PERIOD_MS);
      gpio_set_level(LED1,0);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
  }

void xTask2(void *pvParameters){
  while(1){
      printf("t=1 LED=%d\n",LED2);
      gpio_set_level(LED2,1);
      vTaskDelay(1100 / portTICK_PERIOD_MS);
      gpio_set_level(LED2,0);
      vTaskDelay(1100 / portTICK_PERIOD_MS);
    }
  }
#endif

#ifdef USE_SEMA_BIN
void xTask1(void *pvParameters){
  while(1){
    if( xSemaphoreTake( xSemaphoreBinary, ( TickType_t ) 10 ) == pdTRUE ){
      printf("t=1 LED=%d\n",LED1);
      gpio_set_level(LED1,1);
      vTaskDelay(500 / portTICK_PERIOD_MS);
      gpio_set_level(LED1,0);
      xSemaphoreGive( xSemaphoreBinary );
      vTaskDelay(500 / portTICK_PERIOD_MS);
      }
    }
  }

void xTask2(void *pvParameters){
  while(1){
    if( xSemaphoreTake( xSemaphoreBinary, ( TickType_t ) 10 ) == pdTRUE ){
      printf("t=1 LED=%d\n",LED2);
      gpio_set_level(LED2,1);
      vTaskDelay(1100 / portTICK_PERIOD_MS);
      gpio_set_level(LED2,0);
      xSemaphoreGive( xSemaphoreBinary );
      vTaskDelay(1100 / portTICK_PERIOD_MS);
      }
    }
  }
#endif

