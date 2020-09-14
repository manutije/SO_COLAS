#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct proceso{

  int pid;
  int rafagas_CPU[5];
  int rafagas_ES[5];
  int tiempo_llegada;
};

typedef struct proceso procesos;

procesos proc[20];

void generador_procesos();

int main(void){

  generador_procesos ();

  for(int i=0;i<20;i++){
    printf("\n PROCESO # %d\n",i+1);
    printf("PID: %d\n",proc[i].pid);
    for(int j=0;j<5;j++){
      printf("\nRAFAGAS %d\n",j+1);
      printf("RAFAGA CPU: %d\n",proc[i].rafagas_CPU[j]);
      printf("RAFAGA E/S: %d\n",proc[i].rafagas_ES[j]);
    }
    printf("\n");
    printf("LLEGADA: %d\n",proc[i].tiempo_llegada);
    printf("\n");
  }




}


void generador_procesos(){
  int temp=0;
  srand(time(NULL));

  for(int i =0;i<20;i++){
    proc[i].pid = i;
    for(int j =0;j<5;j++){
      while(temp<10){
        temp =rand()%20;
      }
      proc[i].rafagas_ES[j] = temp;
      temp =0;
      while(temp<1){
        temp =rand()%5;
      }
      proc[i].rafagas_CPU[j] = temp;
    }
    if(i == 0){
      proc[0].tiempo_llegada =0;
    }
    else{
      proc[i].tiempo_llegada =(proc[i-1].tiempo_llegada + (rand()%10));
    }
  }

}
