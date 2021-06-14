#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

typedef struct {
    char *titulo;
    int notaFinal;
    bool aprobada;
    bool cursando;
} Materia;

typedef struct NodoMateria {
    Materia materia;
    struct NodoMateria *proximo;
} NodoMateria;

NodoMateria *agregarMateria(NodoMateria *lista, Materia materia) {
    NodoMateria *nodoNuevo = malloc(sizeof(NodoMateria));
    nodoNuevo->materia = materia;
    nodoNuevo->proximo = NULL;
    if (lista == NULL) {
        lista = nodoNuevo;
    } else {
        NodoMateria *cursor = lista;
        while (cursor->proximo != NULL) {
            cursor = cursor->proximo;
        }
        cursor->proximo = nodoNuevo;
    }
    return lista;
}

NodoMateria *crearListaMaterias() {
    NodoMateria *lista = malloc(sizeof(NodoMateria));
    lista = NULL;
    return lista;
}

int largoDeListaMaterias(NodoMateria *lista){
    if (lista == NULL) {
       return 0;
    } else {
        int contador = 0;
        NodoMateria *cursor = lista;
        while (cursor != NULL) {
            contador = contador+1;
            cursor = cursor->proximo;
        }
        return contador;
    }
    return 0;
}

void eliminarNodoMaterias (NodoMateria *lista, int posicion){
    if(lista == NULL || posicion >= largoDeListaMaterias(lista)){
        return;
    } else{
        NodoMateria *cursor = lista;
        for(int i = 0; i < posicion-1 ;i =i+1){
            cursor = cursor->proximo;
        }
        NodoMateria *proximo = cursor->proximo->proximo;
        free(cursor->proximo);
        cursor->proximo = proximo;
    }
}

void imprimirListaMaterias(NodoMateria *lista){
    if(lista == NULL){
        printf("La lista esta vacia\n");
    }else{
        NodoMateria *cursor = lista;
        while (cursor != NULL) {
            printf("%s, ", cursor->materia.titulo);
            cursor = cursor->proximo;
        }
        printf("\n");
    }
}