#include <stdio.h>
#include <stdlib.h>

typedef struct estructuraEstudiante{
    char *nombre;
    int legajo;
    int edad;
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
    return lista;
}

Nodo *agregarElementoPorEdad(Nodo *lista, Estudiante estudiante) {
    Nodo *nodoNuevo = malloc(sizeof(Nodo));
    nodoNuevo->estudiante = estudiante;
    nodoNuevo->proximo = NULL;
    if (lista == NULL || lista->estudiante.edad > nodoNuevo->estudiante.edad) {
        nodoNuevo->proximo = lista;
        lista = nodoNuevo;
    } else {
        Nodo *cursor = lista;
        while (cursor->proximo != NULL && cursor->proximo->estudiante.edad < nodoNuevo->estudiante.edad) {
            cursor = cursor->proximo;
        }
        if(cursor->proximo != NULL){
            nodoNuevo->proximo = cursor->proximo;
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

Estudiante obtenerEstudiante (Nodo *lista, char *nombre){
    Estudiante estudianteObtenido;
    if(lista == NULL){
        return estudianteObtenido;
    } else{
        Nodo *cursor = lista;
        while(cursor->proximo != NULL && cursor->estudiante.nombre != nombre){
            cursor = cursor->proximo;
        }
        if(cursor->estudiante.nombre == nombre){
            estudianteObtenido = cursor->estudiante;
        }
        return estudianteObtenido;  
    }
}

Nodo *obtenerEstudiantesPorEdad (Nodo *lista, int min, int max){
    Nodo *listaNueva;
    if(lista == NULL){
        return listaNueva;
    } else{
        Nodo *cursor = lista;
        while(cursor != NULL){
            if(cursor->estudiante.edad >= min && cursor->estudiante.edad <= max){
                listaNueva = agregarElementoPorEdad(listaNueva, cursor->estudiante);
            }
            cursor = cursor->proximo;
        }
        return listaNueva;  
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
            printf("%s (%d), ", cursor->estudiante.nombre, cursor->estudiante.edad);
            cursor = cursor->proximo;
        }
        printf("\n");
    }
}