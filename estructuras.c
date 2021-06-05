#include <stdio.h>
#include <stdlib.h>

typedef struct estructuraEstudiante{
    char *nombre;
    int legajo;
} Estudiante;

typedef struct estructuraNodo {
    Estudiante estudiante;
    struct estructuraNodo *proximo;
    
} Nodo;

Nodo *agregarElemento(Nodo *lista, Estudiante estudiante) {
    Nodo *nodoNuevo = malloc(sizeof(Nodo));
    nodoNuevo->estudiante = estudiante;
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

Nodo obtenerNodo (Nodo *lista, int posicion){
    Nodo nodoObtenido;
    if(lista == NULL || posicion >= largoDeLista(lista)){
        return nodoObtenido;
    } else{
        Nodo *cursor = lista;
        for(int i = 0; i < posicion ;i =i+1){
            cursor = cursor->proximo;
        }
        nodoObtenido.estudiante = cursor->estudiante;
        return nodoObtenido;
    }
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
            printf("%s (%d), ", cursor->estudiante.nombre, cursor->estudiante.legajo);
            cursor = cursor->proximo;
        }
        printf("\n");
    }
}