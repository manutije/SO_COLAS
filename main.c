#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct proceso{

  int pid;
  int rafaga;
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
    printf("RAFAGA: %d\n",proc[i].rafaga);
    printf("LLEGADA: %d\n",proc[i].tiempo_llegada);
    printf("\n");
  }




}


void generador_procesos(){
  srand(time(NULL));

  for(int i =0;i<20;i++){
    proc[i].pid = i;
    proc[i].rafaga = rand()%20;
    if(i == 0){
      proc[0].tiempo_llegada =0;
    }
    else{
      proc[i].tiempo_llegada =(proc[i-1].tiempo_llegada + (rand()%10));
    }
  }

}
