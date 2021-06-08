#include <stdio.h>
#include <stdlib.h>
#include "estructura_materias.c"

typedef struct estructuraEstudiante{
    char *nombre;
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
    } else {
        NodoEstudiante *cursor = lista;
        while (cursor->proximo != NULL) {
            cursor = cursor->proximo;
        }
        cursor->proximo = nodoNuevo;
    }
    return lista;
}

NodoEstudiante *agregarElementoPorEdad(NodoEstudiante *lista, Estudiante estudiante) {
    NodoEstudiante *nodoNuevo = malloc(sizeof(NodoEstudiante));
    nodoNuevo->estudiante = estudiante;
    nodoNuevo->proximo = NULL;
    if (lista == NULL || lista->estudiante.edad > nodoNuevo->estudiante.edad) {
        nodoNuevo->proximo = lista;
        lista = nodoNuevo;
    } else {
        NodoEstudiante *cursor = lista;
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

NodoEstudiante *altaEstudiante(char *nombre, int edad, NodoEstudiante *lista){
    Estudiante estudiante;
    estudiante.nombre = nombre;
    estudiante.edad = edad;
    estudiante.materias = crearListaMaterias();
    //Se agrega el alumno a la lista
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

Estudiante obtenerEstudiante (NodoEstudiante *lista, char *nombre){
    Estudiante estudianteObtenido;
    if(lista == NULL){
        return estudianteObtenido;
    } else{
        NodoEstudiante *cursor = lista;
        while(cursor->proximo != NULL && cursor->estudiante.nombre != nombre){
            cursor = cursor->proximo;
        }
        if(cursor->estudiante.nombre == nombre){
            estudianteObtenido = cursor->estudiante;
        }
        return estudianteObtenido;  
    }
}

NodoEstudiante *obtenerEstudiantesPorEdad (NodoEstudiante *lista, int min, int max){
    NodoEstudiante *listaNueva;
    if(lista == NULL){
        return listaNueva;
    } else{
        NodoEstudiante *cursor = lista;
        while(cursor != NULL){
            if(cursor->estudiante.edad >= min && cursor->estudiante.edad <= max){
                listaNueva = agregarElementoPorEdad(listaNueva, cursor->estudiante);
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
            printf("%s (%d), ", cursor->estudiante.nombre, cursor->estudiante.edad);
            cursor = cursor->proximo;
        }
        printf("\n");
    }
}