#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

typedef struct{
    char *titulo;
    int notaFinal;
    bool aprobada;
    bool cursando;
} Materia;

typedef struct estructuraNodo {
    Materia materia;
    struct estructuraNodo *proximo;
} Nodo;

Nodo *agregarElemento(Nodo *lista, Materia materia) {
    Nodo *nodoNuevo = malloc(sizeof(Nodo));
    nodoNuevo->materia = materia;
    nodoNuevo->proximo = NULL;
    if (lista == NULL) {
        lista = nodoNuevo;
    } else {
        Nodo *cursor = lista;
        while (cursor->proximo != NULL) {
            cursor = cursor->proximo;
        }
        cursor->proximo = nodoNuevo;
    }
    return lista;
}

Nodo *crearLista() {
    Nodo *lista = malloc(sizeof(Nodo));
    lista = NULL;
    return lista;
}

int largoDeLista(Nodo *lista){
    if (lista == NULL) {
       return 0;
    } else {
        int contador = 0;
        Nodo *cursor = lista;
        while (cursor != NULL) {
            contador = contador+1;
            cursor = cursor->proximo;
        }
        return contador;
    }
    return 0;
}

void eliminarNodo (Nodo *lista, int posicion){
    if(lista == NULL || posicion >= largoDeLista(lista)){
        return;
    } else{
        Nodo *cursor = lista;
        for(int i = 0; i < posicion-1 ;i =i+1){
            cursor = cursor->proximo;
        }
        Nodo *proximo = cursor->proximo->proximo;
        free(cursor->proximo);
        cursor->proximo = proximo;
    }
}

void imprimirLista(Nodo *lista){
    if(lista == NULL){
        printf("La lista esta vacia\n");
    }else{
        Nodo *cursor = lista;
        while (cursor != NULL) {
            printf("%s, ", cursor->materia.titulo);
            cursor = cursor->proximo;
        }
        printf("\n");
    }
}