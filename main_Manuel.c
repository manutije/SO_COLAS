#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct proceso{

  int pid;
  int rafagas_CPU[11];
  int rafagas_ES[10];
  int tiempo_llegada;
  int cont_rafagas;
  int tiempo_salida;
};

typedef struct proceso procesos;

struct cola_cpu {
  procesos process;
  struct cola_cpu *siguiente;
};

typedef struct cola_cpu Nodo;

Nodo *final;
Nodo *inicio;


struct cola_es {
  procesos process;
  struct cola_es *siguiente;
};

typedef struct cola_es Nodo2;

Nodo2 *final2;
Nodo2 *inicio2;


procesos proc[20];
int contador_global =0;
int cpu_vacio =0;
int cantidad_ES =0;
int cantidad_CPU =0;
void generador_procesos( int ale);
void imprimir_procesos(int ale);
void ordenamiento();
int generar_aleatorio();
int isEmpty();
void enqueue(procesos nuevo_proceso);
void clearBuffer();
int menu();
void nodo_en_cpu();
void agregar_cpu();
void dequeue();
void enqueue2(procesos nuevo_proceso);
void revisar_ES();

int main(void){
  int aleatorio =0;
  aleatorio = generar_aleatorio ();
  generador_procesos (aleatorio);
  ordenamiento ();
  imprimir_procesos (aleatorio);

  //Encolar a todos los procesos en cpu
  for(int i=0;i<20;i++){
    enqueue (proc[i]);
    cantidad_CPU++;
  }
  agregar_cpu ();
  return menu (aleatorio);
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
  FILE *ofp;
  ofp = fopen("procesos.txt","w");

  for(int i=0;i<20;i++){
    printf("\n PROCESO # %d\n",i+1);
    fprintf(ofp,"\n PROCESO # %d\n",i+1);
    printf("PID: %d\n",proc[i].pid);
    fprintf(ofp,"PID: %d\n",proc[i].pid);
    for(int j=0;j<ale+1;j++){
      printf("\nRAFAGAS %d\n",j+1);
      fprintf(ofp,"\nRAFAGAS %d\n",j+1);
      printf("RAFAGA CPU: %d\n",proc[i].rafagas_CPU[j]);
      fprintf(ofp,"RAFAGA CPU: %d\n",proc[i].rafagas_CPU[j]);
      if(j<ale){
        printf("RAFAGA E/S: %d\n",proc[i].rafagas_ES[j]);
        fprintf(ofp,"RAFAGA E/S: %d\n",proc[i].rafagas_ES[j]);
      }
    }
    printf("\n");
    fprintf(ofp,"\n");
    printf("LLEGADA: %d\n",proc[i].tiempo_llegada);
    fprintf(ofp,"LLEGADA: %d\n",proc[i].tiempo_llegada);
    printf("\n");
    fprintf(ofp,"\n");
  }
  fclose(ofp);
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


// agrega un nodo nuevo al final de la cola
void enqueue(procesos nuevo_proceso) {
  Nodo *nodoNuevo,
       *temporal;

  nodoNuevo = (Nodo*) malloc(sizeof(Nodo));


  nodoNuevo->process = nuevo_proceso;
  nodoNuevo->process.cont_rafagas = 0;
  nodoNuevo->process.tiempo_salida=0;

  printf("\nAgregando a la cola de cpu el proceso %d\n",nodoNuevo->process.pid);
  if (isEmpty()) { // si la cola esta vacia
    final = nodoNuevo; // el nodo toma el primer
    inicio = nodoNuevo; // y el ultimo lugar
  } else { // si hay al menos 1 nodo
    temporal = final; // almacenamos el ultimo nodo agregado
    final = nodoNuevo; // el nodoNuevo toma el primer lugar
    final->siguiente = temporal; // apuntando al nodo que estaba en primer lugar
  }
}

int isEmpty() {
  if (!final) {
    return 1;
  } else {
    return 0;
  }
}

int menu(int ale) {
  char c;

  do {
    printf("\n~~ MENU: Simulador ~~");
    printf("\n\nTiempo de la simulacion: %d",contador_global);
    printf("\nHaga una seleccion:");
    printf("\n 1. Limpiar pantalla");
    printf("\n 2. Avanzar");
    printf("\n 3. Terminar");
    printf("\n q: salir.\n");
    c = getchar();
    switch(c) {
      case '1':
        system ("clear");
        clearBuffer ();
        break;
      case '2':
        printf("\n\n Avanzar");
        agregar_cpu ();
        nodo_en_cpu (ale);
        revisar_ES ();
        contador_global++;
        clearBuffer ();
        break;
      case '3':
        printf("\n\nTerminar");
        clearBuffer ();
        break;
      default:
        break;
    }
  } while(c != 'q' && c != EOF);

  return 1;
}

void clearBuffer() {
  while(getchar() != '\n')
    ;
}

void nodo_en_cpu(int ale){
  printf("\n\n Nodo que se encuentra actualmente en el CPU");
  printf("\nPID: %d",inicio->process.pid);
  printf("\nTiempo de llegada: %d",inicio->process.tiempo_llegada);
  printf("\nTiempo de salida: %d",inicio->process.tiempo_salida);
  printf("\nRafagas que ha ejecutado este proceso: %d de %d",inicio->process.cont_rafagas+1,ale+1);
}
void agregar_cpu(){
  if(cpu_vacio == 0){
    inicio->process.tiempo_salida =contador_global+inicio->process.rafagas_CPU[inicio->process.cont_rafagas];
    cpu_vacio =1;
  }
  if(cpu_vacio == 1){
    if(inicio->process.tiempo_salida == contador_global){
      printf("\nYa acabo de usar CPU el proceso con PID: %d",inicio->process.pid);
      inicio->process.cont_rafagas++;
      enqueue2 (inicio->process);
      cantidad_ES++;
      cantidad_CPU--;
      dequeue ();
      cpu_vacio =0;
      agregar_cpu ();
    }

  }
}

void dequeue() {
  Nodo *actual,
       *temporal;


  clearBuffer();

  if (isEmpty()) {
  } else {
    if (final == inicio) { // si solo hay 1 nodo
      free(final); // liberamos la memoria que uso el nodo
      free(inicio); // liberamos la memoria que uso el nodo
      final = inicio = 0; // dejamos los punteros en null
    } else { // si hay mas de 1 nodo
      actual = final;
      while (actual != inicio) { // recorra la cola y quede en el penultimo
        temporal = actual; // temporal guarda la direccion del penultimo
        actual = temporal->siguiente;
      }
      free(inicio); // liberamos la memoria usada por el ultimo nodo
      inicio = temporal; // el penultimo es ahora el ultimo
    }
  }
}


void enqueue2(procesos nuevo_proceso) {
  Nodo2 *nodoNuevo,
       *temporal;
  nodoNuevo = (Nodo2*) malloc(sizeof(Nodo2));
  nodoNuevo->process = nuevo_proceso;
  nodoNuevo->process.tiempo_salida=contador_global+nodoNuevo->process.rafagas_ES[nodoNuevo->process.cont_rafagas-1];

  printf("\nAgregando a la cola de Entradas y Salidas\n");
  printf("\nEl tiempo de salida de esta cola es: %d\n",nodoNuevo->process.tiempo_salida);
  if (!final2) { // si la cola esta vacia
    final2 = nodoNuevo; // el nodo toma el primer
    inicio2 = nodoNuevo; // y el ultimo lugar
  } else { // si hay al menos 1 nodo
    temporal = final2; // almacenamos el ultimo nodo agregado
    final2 = nodoNuevo; // el nodoNuevo toma el primer lugar
    final2->siguiente = temporal; // apuntando al nodo que estaba en primer lugar
  }
}

void revisar_ES(){
  int tamano =0;
  Nodo2 *temporal;
  if (!final2){
    printf("\nLa cola de Entradas y salidas se encuentra vacia\n");
  }
  else{
    temporal = final2;
    for(int i=0;i<cantidad_ES;i++){
      printf("\nEn la cola de Entradas y salidas se encuentra el Proceso %d con tiempo de salida de %d",temporal->process.pid,temporal->process.tiempo_salida);
      if(temporal != inicio2){
        temporal = temporal->siguiente;
      }
    }
  }
}


