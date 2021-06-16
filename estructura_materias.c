#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

typedef struct {
    char titulo[100];
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
        strcpy(materia.titulo, titulo);
        materia.aprobada = false;
        materia.cursando = true;
        materia.notaFinal = NULL;
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

Materia obtenerMateria(NodoMateria *lista, int codigo){
    Materia materia;
    if (lista == NULL) {
       return materia;
    } else {
        NodoMateria *cursor = lista;
        while (cursor->proximo != NULL && cursor->materia.codigo != codigo) {
            cursor = cursor->proximo;
        }
        if(cursor->materia.codigo == codigo){
            materia = cursor->materia;
        }
        return materia;
    }
}

NodoMateria *rendir(NodoMateria *lista, int codigo, int nota){
    if (lista == NULL) {
       return lista;
    } else {
        NodoMateria *cursor = lista;
        while (cursor->proximo != NULL && cursor->materia.codigo != codigo) {
            cursor = cursor->proximo;
        }
        if(cursor->materia.codigo == codigo){
            cursor->materia.notaFinal = nota;
            if(nota >= 4) cursor->materia.aprobada = true;
            cursor->materia.cursando = false;
        }
        return lista;
    }
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
        int contador = 0;
        printf("    Titulo      Codigo\n");
        while (cursor != NULL) {
            contador = contador + 1;
            printf("%i.  %s   %d\n", contador, cursor->materia.titulo, cursor->materia.codigo);
            cursor = cursor->proximo;
        }
        printf("\n");
    }
}

void imprimirMateriasDelAlumno(NodoMateria *lista){
    if(lista == NULL){
        printf("La lista esta vacia\n");
    }else{
        NodoMateria *cursor = lista;
        int contador = 0;
        printf("    Titulo   Nota   Codigo\n");
        while (cursor != NULL) {
            contador = contador + 1;
            printf("%i.  %s  %d   %d\n", contador, cursor->materia.titulo, cursor->materia.notaFinal, cursor->materia.codigo);
            cursor = cursor->proximo;
        }
        printf("\n");
    }
}