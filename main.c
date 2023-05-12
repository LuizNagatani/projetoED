#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "headers/heap/FD.h"
//#include "headers/stack/PD.h"

#define MAX  100

typedef struct Node{

    int *info;
   struct  Node *next;

}node;



typedef struct{
struct Node *ini;
struct Node *fim;

}fila;

typedef struct Anime{
int eps;
int baixados;
int assistidos;
char nome [MAX];
fila *queue
}anime;

typedef struct {
struct Node *topo;
struct Anime *a;
}pilha;
fila*criafila(){
  fila*f = (fila*)malloc(sizeof(fila));
  f->ini = NULL;
  f->fim = NULL;
  return f;
}
pilha*comeca(pilha *p, char E, int A){
    printf("comeca serie %c com %d episodios", E, A);
    
    node*novo = (node*)malloc(sizeof(node));
    novo->info = E;
    novo->next = p->topo;
    p->topo = novo;
    return p;
}
pilha*push(pilha*p, anime *a, int A){//pilha ligada

    node*novo = (node*)malloc(sizeof(node));
    novo->info = a;
    novo->next = p->topo;
    p->topo = novo;
    a->eps=A;
   
   
}
int pop(pilha *p) {
  node *pt = p->topo;
  if(p->topo == NULL) return;
node *aux = pt->next; 
  int valor= pt->info;
free(p->topo);
p->topo = aux;
  return valor;

}
fila* pushfila(fila *f, int x){
  node*novo = (node*)malloc(sizeof(node));
  novo->info = x;
  if(f->fim == NULL){
  f->ini= novo;
    f->fim =novo;
  }
  
  else{
    f->fim->next = novo;
    f->fim = novo;
  } 
novo ->next = NULL;

}
int pilhaVazia(pilha *p) {
    return (p->topo == NULL); // Retorna verdadeiro se o topo da pilha for nulo
}
int filaVazia(fila *p) {
    return (p->ini == NULL); // Retorna verdadeiro se o topo da pilha for nulo
}
void popfila(fila*f){
  if (f->ini != NULL) {
    node *temp = f->ini;
    f->ini = f->ini->next;
    
    free(temp);
  } else {
    printf("Fila vazia\n");
  }
}
char compareStrings(pilha *list, char *S, char *E){
    char S_compare_start[]="comeca", S_compare_download[]="download", S_compare_assiste[]="assiste";

    int A, t;
    if(strcmp(S, S_compare_start) == 0){
        scanf("%s %d", E, &A);
      anime*a=(anime*)malloc(sizeof(anime));
       
      list->a = a;
        fila*f = criafila();
      list->a->queue = f;
      push(list, a, A);
      list->a->baixados = 0;//teste
      printf("comecando %s com %d episodios\n", E, A);
        
        //função funcionando perfeitamente;


    }else
    if(strcmp(S, S_compare_download) == 0){
        scanf("%d %d", &A, &t);
      int i = 0;
    if(list->a->eps > list->a->baixados){
      for (i=0; i<=A-1; i++){
        if(list->a->eps <= list->a->baixados) break;
           pushfila(list->a->queue, list->a->baixados+1);
          
        list->a->baixados++;
      }
      printf("%d episodios de %s baixados\n", A, E);
    }
      
      
      
     if(list->a->eps <= list->a->baixados){
        printf("não há episódios para baixar");
      }
       printf("Fila:%d ",filaVazia(list->a->queue) );
  node *temp = list->a->queue->ini;
  while (temp != NULL) {
    printf("%d ", temp->info);
    temp = temp->next;
  }
  printf("\n");
    }
 if(strcmp(S, S_compare_assiste) == 0){
    scanf("%d", &A);
    
    
    int i = 0;
   if(filaVazia(list->a->queue) == 0){
    for (i=0; i==A; i++){
  
        popfila(list->a->queue);
    printf("Assistido %d episodios de %s, (%d minutos)\n", A, E, A*t);
      
    }
      if(filaVazia(list->a->queue) == 1){
        pop(list);
        printf("acabou %s\n",E);
      }
    }
    return S;
}

}

int main(){
	/*
	 * S --> instruction "start"
	 * E --> name of the show
	 * A --> nº of episodes
	 * */
    


	char S[6], E[MAX],  S_compare_exit[] = "f";
    pilha*p = (pilha*)malloc(sizeof(pilha));
    p->topo = NULL;
	while(1){
        scanf("%s", S);
        if(strcmp(S, S_compare_exit) == 0){
            return 0;
        }
        compareStrings(p ,S, E);
    }


	return 0;
}

