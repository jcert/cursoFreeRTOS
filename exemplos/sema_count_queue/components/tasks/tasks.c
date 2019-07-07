#include <stdio.h>

#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "tasks.h"

extern SemaphoreHandle_t xSemaphoreCounting;
extern QueueHandle_t xQueuePinosLED;

void xTask_period1(void *pvParameters){
  uint8_t led = 0;
  while(1){
    if( pdTRUE == xSemaphoreTake(xSemaphoreCounting,1000) ){
      //presumo que o semáforo já cuide de a fila nunca estar vazia
      xQueueReceive(xQueuePinosLED,&led,1);
      printf("t=1 LED=%d\n",led);
      gpio_set_level(led,1);
      vTaskDelay(500 / portTICK_PERIOD_MS);
      gpio_set_level(led,0);
      vTaskDelay(500 / portTICK_PERIOD_MS);
      xQueueSend(xQueuePinosLED,&led,1);
      xSemaphoreGive(xSemaphoreCounting);
      
      //pare por 1s
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
    }
  }

void xTask_period2(void *pvParameters){
  uint8_t led = 0;
  while(1){
    if( pdTRUE == xSemaphoreTake(xSemaphoreCounting,1000) ){
      //presumo que o semáforo já cuide de a fila nunca estar vazia
      xQueueReceive(xQueuePinosLED,&led,1);
      printf("t=2 LED=%d\n",led);
      gpio_set_level(led,1);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      gpio_set_level(led,0);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      xQueueSend(xQueuePinosLED,&led,1);
      xSemaphoreGive(xSemaphoreCounting);
      
      //pare por 1s
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
    }
  }

void xTask_period4(void *pvParameters){
  uint8_t led = 0;

  while(1){
    if( pdTRUE == xSemaphoreTake(xSemaphoreCounting,1000) ){
      //presumo que o semáforo já cuide de a fila nunca estar vazia
      xQueueReceive(xQueuePinosLED,&led,1);
      printf("t=4 LED=%d\n",led);
      gpio_set_level(led,1);
      vTaskDelay(2000 / portTICK_PERIOD_MS);
      gpio_set_level(led,0);
      vTaskDelay(2000 / portTICK_PERIOD_MS);
      xQueueSend(xQueuePinosLED,&led,1);
      xSemaphoreGive(xSemaphoreCounting);
      
      //pare por 1s
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
    }
  }


void xTask_period8(void *pvParameters){
  uint8_t led = 0;

  while(1){
    if( pdTRUE == xSemaphoreTake(xSemaphoreCounting,1000) ){
      //presumo que o semáforo já cuide de a fila nunca estar vazia
      xQueueReceive(xQueuePinosLED,&led,1);
      printf("t=8 LED=%d\n",led);
      gpio_set_level(led,1);
      vTaskDelay(4000 / portTICK_PERIOD_MS);
      gpio_set_level(led,0);
      vTaskDelay(4000 / portTICK_PERIOD_MS);
      xQueueSend(xQueuePinosLED,&led,1);
      xSemaphoreGive(xSemaphoreCounting);
      
      //pare por 1s
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
    }
  }

void xTask_period16(void *pvParameters){
  uint8_t led = 0;

  while(1){
    if( pdTRUE == xSemaphoreTake(xSemaphoreCounting,1000) ){
      //presumo que o semáforo já cuide de a fila nunca estar vazia
      xQueueReceive(xQueuePinosLED,&led,1);
      printf("t=16 LED=%d\n",led);
      gpio_set_level(led,1);
      vTaskDelay(8000 / portTICK_PERIOD_MS);
      gpio_set_level(led,0);
      vTaskDelay(8000 / portTICK_PERIOD_MS);
      xQueueSend(xQueuePinosLED,&led,1);
      xSemaphoreGive(xSemaphoreCounting);
      
      //pare por 1s
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
    }
  }

