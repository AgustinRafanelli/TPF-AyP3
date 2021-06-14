#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructura_materias.c"

typedef struct estructuraEstudiante{
    char nombre[64];
    int legajo;
    int edad;
    NodoMateria *materias;

} Estudiante;

typedef struct NodoEstudiante {
    Estudiante estudiante;
    struct NodoEstudiante *proximo;
    
} NodoEstudiante;

NodoEstudiante *agregarElemento(NodoEstudiante *lista, Estudiante estudiante) {
    NodoEstudiante *nodoNuevo = malloc(sizeof(NodoEstudiante));
    nodoNuevo->estudiante = estudiante;
    nodoNuevo->proximo = NULL;
    if (lista == NULL) {
        lista = nodoNuevo;
      //  nodoNuevo->estudiante.legajo = 1;
    } else {
        NodoEstudiante *cursor = lista;
        while (cursor->proximo != NULL) {
            cursor = cursor->proximo;
        }
       // nodoNuevo->estudiante.legajo = cursor->estudiante.legajo+1;
        cursor->proximo = nodoNuevo;
    }
    return lista;
}

NodoEstudiante *agregarElementoPorEdad(NodoEstudiante *lista, Estudiante estudiante) {
    NodoEstudiante *nodoNuevo = malloc(sizeof(NodoEstudiante));
    nodoNuevo->estudiante = estudiante;
    nodoNuevo->proximo = NULL;
    printf("elemento\n");
    if (lista == NULL || lista->estudiante.edad > nodoNuevo->estudiante.edad) {
        printf("primer elemento\n");
        nodoNuevo->proximo = lista;
        lista = nodoNuevo;
    } else {
        NodoEstudiante *cursor = lista;
        while (cursor->proximo != NULL && cursor->proximo->estudiante.edad < nodoNuevo->estudiante.edad) {
            printf("while por edad\n");
            cursor = cursor->proximo;
        }
        if(cursor->proximo != NULL){
            printf("ultimo elemento\n");
            nodoNuevo->proximo = cursor->proximo;
        }
        cursor->proximo = nodoNuevo;
    }
    printf("return");
    return lista;
}

NodoEstudiante *altaEstudiante(char *nombre, int edad, NodoEstudiante *lista){
    Estudiante estudiante;
    strcpy(estudiante.nombre, nombre);
    estudiante.edad = edad;
    estudiante.materias = crearListaMaterias();
    lista = agregarElemento(lista, estudiante);
    return lista;
}

NodoEstudiante *crearLista() {
    NodoEstudiante *lista = malloc(sizeof(NodoEstudiante));
    lista = NULL;
    return lista;
}

int largoDeLista(NodoEstudiante *lista){
    if (lista == NULL) {
       return 0;
    } else {
        int contador = 0;
        NodoEstudiante *cursor = lista;
        while (cursor != NULL) {
            contador = contador+1;
            cursor = cursor->proximo;
        }
        return contador;
    }
    return 0;
}

NodoEstudiante *obtenerEstudiante (NodoEstudiante *lista, char *nombre){
    NodoEstudiante *listaNueva;
    printf("%s", nombre);
    if(lista == NULL){
        
        printf("lista null");
        return listaNueva;
    } else{
        NodoEstudiante *cursor = lista;
        while(cursor != NULL){
            printf("while\n %s", cursor->estudiante.nombre);
            if(cursor->estudiante.nombre == nombre){
                printf("if");
                listaNueva = agregarElemento(listaNueva, cursor->estudiante);
            }
            cursor = cursor->proximo;
        }
        return listaNueva;  
    }
}

NodoEstudiante *obtenerEstudiantesPorEdad (NodoEstudiante *lista, int min, int max){
    NodoEstudiante *listaNueva;
    if(lista == NULL){
        printf("null\n");
        return listaNueva;
    } else{
        NodoEstudiante *cursor = lista;
        while(cursor != NULL){
            printf("while\n");
            if(cursor->estudiante.edad >= min && cursor->estudiante.edad <= max){
                printf("if\n");
                listaNueva = agregarElementoPorEdad(listaNueva, cursor->estudiante);
                printf("otro if\n");
            }
            cursor = cursor->proximo;
        }
        return listaNueva;  
    }
}

void eliminarNodo (NodoEstudiante *lista, int posicion){
    if(lista == NULL || posicion >= largoDeLista(lista)){
        return;
    } else{
        NodoEstudiante *cursor = lista;
        for(int i = 0; i < posicion-1 ;i =i+1){
            cursor = cursor->proximo;
        }
        NodoEstudiante *proximo = cursor->proximo->proximo;
        free(cursor->proximo);
        cursor->proximo = proximo;
    }
}

void imprimirLista(NodoEstudiante *lista){
    if(lista == NULL){
        printf("La lista esta vacia\n");
    }else{
        NodoEstudiante *cursor = lista;
        while (cursor != NULL) {
            printf("%s (%d) Leg: %d, ", cursor->estudiante.nombre, cursor->estudiante.edad, cursor->estudiante.legajo);
            cursor = cursor->proximo;
        }
        printf("\n");
    }
}