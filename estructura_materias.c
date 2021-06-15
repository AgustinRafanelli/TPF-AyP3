#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

typedef struct {
    char *titulo;
    int notaFinal;
    int codigo;
    bool aprobada;
    bool cursando;
} Materia;

typedef struct NodoMateria {
    Materia materia;
    struct NodoMateria *proximo;
} NodoMateria;

NodoMateria *crearListaMaterias() {
    NodoMateria *lista = malloc(sizeof(NodoMateria));
    lista = NULL;
    return lista;
}

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

NodoMateria *agregarNuevaMateria(NodoMateria *lista, Materia materia) {
    NodoMateria *nodoNuevo = malloc(sizeof(NodoMateria));
    nodoNuevo->materia = materia;
    nodoNuevo->proximo = NULL;
    if (lista == NULL) {
        lista = nodoNuevo;
        nodoNuevo->materia.codigo = 1;
    } else {
        NodoMateria *cursor = lista;
        while (cursor->proximo != NULL) {
            cursor = cursor->proximo;
        }
        nodoNuevo->materia.codigo = cursor->materia.codigo+1;
        cursor->proximo = nodoNuevo;
    }
    return lista;
}

bool verificarRepeticion(NodoMateria *lista, char *titulo){
    if(lista == NULL){
        return false;
    } else{
        NodoMateria *cursor = lista;
        while(cursor != NULL){
            if(strcmp(cursor->materia.titulo, titulo) == 0){
                return true;
            }
            cursor = cursor->proximo;
        }
        return false;
    }
}

NodoMateria *altaMateria(char *titulo, NodoMateria *lista){
    if(verificarRepeticion(lista, titulo) == false){
        Materia materia;
        materia.titulo = titulo;
        lista = agregarNuevaMateria(lista, materia);
    } 
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