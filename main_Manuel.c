#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct proceso{

  int pid;
  int rafagas_CPU[11];
  int rafagas_ES[10];
  int tiempo_llegada;
};

typedef struct proceso procesos;

procesos proc[20];
void generador_procesos( int ale);
void imprimir_procesos(int ale);
void ordenamiento();
int generar_aleatorio();

int main(void){
  int aleatorio =0;
  aleatorio = generar_aleatorio ();
  generador_procesos (aleatorio);
  ordenamiento ();
  imprimir_procesos (aleatorio);
}


void generador_procesos(int ale){
  int temp=0;
  srand(time(NULL));

  for(int i =0;i<20;i++){
    proc[i].pid = i;
    for(int j =0;j<ale+1;j++){
      while(temp<10){
        temp =rand()%20;
      }
      if(j<ale){
        proc[i].rafagas_ES[j] = temp;
      }
      temp =0;
      while(temp<1){
        temp =rand()%8;
      }
      proc[i].rafagas_CPU[j] = temp;
    }
    if(i == 0){
      proc[0].tiempo_llegada =0;
    }
    else{
      proc[i].tiempo_llegada =rand()%20;
    }
  }
}


void imprimir_procesos(int ale){
  for(int i=0;i<20;i++){
    printf("\n PROCESO # %d\n",i+1);
    printf("PID: %d\n",proc[i].pid);
    for(int j=0;j<ale+1;j++){
      printf("\nRAFAGAS %d\n",j+1);
      printf("RAFAGA CPU: %d\n",proc[i].rafagas_CPU[j]);
      if(j<ale){
        printf("RAFAGA E/S: %d\n",proc[i].rafagas_ES[j]);
      }
    }
    printf("\n");
    printf("LLEGADA: %d\n",proc[i].tiempo_llegada);
    printf("\n");
  }
}

int generar_aleatorio()
{
  srand(time(NULL));
  int aleatorio =0;
  while(aleatorio<5){
    aleatorio=rand()%10;
  }
  return aleatorio;
}

void ordenamiento(){

  procesos tempo;

  for(int i=0;i<20;i++){
    for(int j=i+1;j<20;j++){

      if(proc[i].tiempo_llegada > proc[j].tiempo_llegada){
        tempo = proc[j];
        proc[j] = proc[i];
        proc[i] = tempo;
      }

      if(proc[j].tiempo_llegada == proc[i].tiempo_llegada){
        if(proc[i].pid > proc[j].pid){
          tempo = proc[j];
          proc[j] = proc[i];
          proc[i] = tempo;
        }
      }

    }
  }
}
