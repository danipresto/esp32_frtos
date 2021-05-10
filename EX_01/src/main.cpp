/*
       COMO CRIAR  TAREFAS NO FREERTOS
*/


// Bibliotecas
#include <Arduino.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


//Pinos
#define LED 2

//Variaveis
TaskHandle_t task1handle = NULL;
TaskHandle_t task2handle = NULL;

//Prototipo das tasks

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

void setup() {

  // put your setup code here, to run once:

  Serial.begin(9600);
  
  xTaskCreate(vTask1,"TASK 1", configMINIMAL_STACK_SIZE,NULL,1,&task1handle);
  xTaskCreate(vTask2,"TASK 2", configMINIMAL_STACK_SIZE+1024,NULL,2,&task2handle);

}

void loop() {
  // put your main code here, to run repeatedly:
  vTaskDelay(1000);

}

void vTask1(void *pvParameters){

  pinMode(LED,OUTPUT);

  while(1){
      digitalWrite(LED,!digitalRead(LED));
      vTaskDelay(pdMS_TO_TICKS(100));
  }

}

void vTask2(void *pvParameters){

    int cont = 0;

    while(1){
        Serial.println("Task 2: " + String(cont++));
        if(cont==10){
          vTaskSuspend(task1handle);
          Serial.println("TASK SUSPENSA");
          digitalWrite(2,LOW);
        }
        else if(cont==15){
          Serial.println("TASK CONTINUADA");
          vTaskResume(task1handle);
        }
        vTaskDelay(pdMS_TO_TICKS(500));

    }

}
