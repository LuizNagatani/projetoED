#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
    char nome[50];
    int episode_num;
    int duracao;
    struct Nodo *prox;
} Nodo;

typedef struct {
    Nodo *topo;
} pilha;

void push(pilha *s, char *nome) {
    Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
    strcpy(novo->nome, nome);
    novo->prox = s->topo;
    s->topo = novo;
}
void pop(pilha *p) {
  
  if(p->topo >= 0) p->topo--;
}
typedef struct {
    Nodo *ini;
    Nodo *fim;
    int maximo;
    int baixados;
} Fila;

typedef struct {
    Fila animes[10];
    int num_animes;
} Anime;

Fila *get_queue(Anime *q, char *nome) {
    for (int i = 0; i < q->num_animes; i++) {
        if (strcmp(q->animes[i].ini->nome, nome) == 0) {
            return &q->animes[i];
        }
    }
    
    q->num_animes++;
    q->animes[q->num_animes - 1].ini = NULL;
    q->animes[q->num_animes - 1].fim = NULL;
    return &q->animes[q->num_animes - 1];
}

int enqueue(Fila *queue, pilha *s, int num_episodios, int duracao) {
    int count = 0, i;
    Nodo *temp = queue->ini;
    while (temp != NULL) {
        count++;
        temp = temp->prox;
    }
   
    for (i = 0; i <= num_episodios-1; i++) {
        if(queue->baixados== queue->maximo) break;
        Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
        strcpy(novo->nome, s->topo->nome);
        novo->episode_num = i;
        novo->duracao = duracao;
        novo->prox = NULL;
        queue->baixados++;

        if (queue->fim == NULL) {
            queue->ini = novo;
            queue->fim = novo;
        } else {
            queue->fim->prox = novo;
            queue->fim = novo;
        }
    }
  return i;
}

Nodo dequeue(Fila *f) {
    Nodo temp = *(f->ini);
    Nodo *temp_ptr = f->ini;
    f->ini = f->ini->prox;
    if (f->ini == NULL) {
        f->fim = NULL;
    }
    free(temp_ptr);
    return temp;
}

void print_queue(Fila *queue) {
    if (queue->ini == NULL) {
        printf("Fila vazia\n");
        return;
    }
    Nodo *temp = queue->ini;
    while (temp != NULL) {
        printf("%s %d ", temp->nome, temp->episode_num);
        temp = temp->prox;
    }
    printf("\n");
}

void print_remaining(Anime *q) {
    int restante = 0;
    for (int i = 0; i < q->num_animes; i++) {
        Fila *queue = &q->animes[i];
        if (queue->ini != NULL) {
            restante++;
            int count = 0;
            Nodo *temp = queue->ini;
            while (temp != NULL) {
                count++;
                temp = temp->prox;
            }
            printf("ha %d episodios sobrando de %s de %d\n", queue->maximo, queue->ini->nome, count);
        }
    }
    if (restante == 0) {
        printf("sem episodios para assistir\n");
    }
}

int main() {
    pilha s = {.topo = NULL};
    Anime q = {.num_animes = 0};
    char comando[10];
    char nome[50];
    int num_episodios, duracao;
    int tempo_restante = 0;
    Fila *atual = NULL;
    int primeiro_comando = 1;
    while (1) {

        scanf("%s", comando);

        if (strcmp(comando, "f") == 0) {
            print_remaining(&q);
            break;
        } else if (strcmp(comando, "comeca") == 0) {
            scanf("%s %d", nome, &num_episodios);
            printf("comecando %s com %d episodios\n", nome, num_episodios);
            push(&s, nome);
            atual = get_queue(&q, nome);
            atual->maximo = num_episodios;
            primeiro_comando = 0;
        } else if (strcmp(comando, "download") == 0) {
            if (primeiro_comando) {
                printf("nao ha episodios para baixar\n");
                continue;
            }
            scanf("%d %d", &num_episodios, &duracao);
           int i = enqueue(atual, &s, num_episodios, duracao);
          if (i == 0){
            printf("nao ha episodios para baixar", nome);
          
          }
          else printf("%d episodios baixados de %s\n", i, nome);
        } else if (strcmp(comando, "assiste") == 0) {
          if(atual->ini>atual->fim && s.topo > 0){
              printf("acabou %s", nome);
           pop(&s);
              }
            if (primeiro_comando) {
                printf("nao ha animes para assistir\n");
                continue;
            }
            scanf("%d", &num_episodios);

            if (atual->ini == NULL && s.topo != NULL) {
                Nodo *temp_ptr = s.topo;
                s.topo = s.topo->prox;
                free(temp_ptr);
                atual = get_queue(&q, s.topo->nome);
                printf("nao ha mais episodios de %s para assistir\n", s.topo->prox->nome);
                continue;
            } else if (atual->ini == NULL && s.topo == NULL) {
                printf("nao ha mais episodios de %s para assistir\n", s.topo->nome);
                continue;
            }

            Nodo temp = *(atual->ini);
            tempo_restante += (atual->fim - atual->ini + 1) * temp.duracao;
            int count = 0;
            Nodo *temp_ptr = atual->ini;
            while (temp_ptr != NULL) {
                count++;
                temp_ptr = temp_ptr->prox;
            }
            if (num_episodios > count) {
                printf("apenas %d restantes\n", count);
                tempo_restante -= count * temp.duracao;
                printf("%d episodios assistidos (%d minutoss)\n", count, count * temp.duracao);
                while (atual->ini != NULL && strcmp(atual->ini->nome, s.topo->nome) == 0) {
                    dequeue(atual);
                }
              
                if (s.topo != NULL) {
                    Nodo *temp_ptr = s.topo;
                    s.topo = s.topo->prox;
                    free(temp_ptr);
                }
                atual = get_queue(&q, s.topo->nome);
            } else {
                tempo_restante -= num_episodios * temp.duracao;
                printf("%d episodios de %s assistidos (%d minutos)\n", num_episodios, s.topo->nome, num_episodios * temp.duracao);
                for (int i = 0; i < num_episodios && atual->ini != NULL && strcmp(atual->ini->nome, s.topo->nome) == 0; i++) {
                    dequeue(atual);
                }
            }
        } else if (strcmp(comando, "print_queue") == 0) {
            print_queue(atual);
        }
    }
    return 0;
}


