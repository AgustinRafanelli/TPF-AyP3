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

NodoEstudiante *agregarNuevoEstudiante(NodoEstudiante *lista, Estudiante estudiante) {
    NodoEstudiante *nodoNuevo = malloc(sizeof(NodoEstudiante));
    nodoNuevo->estudiante = estudiante;
    nodoNuevo->proximo = NULL;
    if (lista == NULL) {
        lista = nodoNuevo;
        nodoNuevo->estudiante.legajo = 1;
    } else {
        NodoEstudiante *cursor = lista;
        while (cursor->proximo != NULL) {
            cursor = cursor->proximo;
        }
        nodoNuevo->estudiante.legajo = cursor->estudiante.legajo+1;
        cursor->proximo = nodoNuevo;
    }
    return lista;
}

NodoEstudiante *altaEstudiante(char *nombre, int edad, NodoEstudiante *lista){
    Estudiante estudiante;
    strcpy(estudiante.nombre, nombre);
    estudiante.edad = edad;
    estudiante.materias = crearListaMaterias();
    lista = agregarNuevoEstudiante(lista, estudiante);
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

bool verificarEstudiante(NodoEstudiante *lista, int legajo){
    if (lista == NULL) {
       return false;
    } else {
        NodoEstudiante *cursor = lista;
        while (cursor->proximo != NULL && cursor->estudiante.legajo != legajo) {
            cursor = cursor->proximo;
        }
        if(cursor->estudiante.legajo == legajo){
            return true;
        }
        return false;
    }
}

NodoEstudiante *modificarEstudianteActual(NodoEstudiante *lista, int legajo){
    if (lista == NULL) {
       return lista;
    } else {
        NodoEstudiante *cursor = lista;
        while (cursor->proximo != NULL && cursor->estudiante.legajo != legajo) {
            cursor = cursor->proximo;
        }
        if(cursor->estudiante.legajo == legajo){
            return cursor;
        }
    }
}

NodoEstudiante *obtenerEstudiante (NodoEstudiante *lista, char *nombre){
    NodoEstudiante *listaNueva = crearLista();
    if(lista == NULL){
        return listaNueva;
    } else{
        NodoEstudiante *cursor = lista;
        while(cursor != NULL){
            if(strcmp(cursor->estudiante.nombre, nombre) == 0){
                listaNueva = agregarElemento(listaNueva, cursor->estudiante);
            }
            cursor = cursor->proximo;
        }
        return listaNueva;  
    }
}

Estudiante obtenerEstudianteLegajo (NodoEstudiante *lista, int legajo){
    Estudiante estudiante;
    if(lista == NULL){
        return estudiante;
    } else{
        NodoEstudiante *cursor = lista;
        while(cursor != NULL && cursor->estudiante.legajo != legajo){
            cursor = cursor->proximo;
        }
        if(cursor->estudiante.legajo == legajo) estudiante = cursor->estudiante;
        return estudiante;  
    }
}

NodoEstudiante *obtenerEstudiantesPorEdad (NodoEstudiante *lista, int min, int max){
    NodoEstudiante *listaNueva = crearLista();
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

void eliminarEstudiante (NodoEstudiante **lista, int legajo){
    NodoEstudiante *proximo;
    NodoEstudiante *cursor = *lista;
    if(lista == NULL){
        return;
    }else if(cursor->estudiante.legajo == legajo){
        proximo = *lista;
        *lista = (*lista)->proximo;
        free(proximo);
    }else{
        while (cursor->proximo != NULL && cursor->proximo->estudiante.legajo != legajo) {
            cursor = cursor->proximo;
        }
        if(cursor->proximo->proximo == NULL && cursor->proximo->estudiante.legajo == legajo){
            cursor->proximo = NULL;
        }else if(cursor->proximo->estudiante.legajo == legajo){
            proximo = cursor->proximo->proximo;
            free(cursor->proximo);
            cursor->proximo = proximo;
        }
    }
}

void imprimirLista(NodoEstudiante *lista){
    if(lista == NULL){
        printf("La lista esta vacia\n");
    }else{
        NodoEstudiante *cursor = lista;
        int contador = 0;
        int contadorTotal = 0;
        printf("\n    Nombre y Apellido      Edad  Legajo\n\n");
        while (cursor != NULL && contador < 5) {
            contador = contador + 1;
            if(strlen(cursor->estudiante.nombre) == 19){
                printf("%i.  %s     %d     %d\n", contador, cursor->estudiante.nombre, cursor->estudiante.edad, cursor->estudiante.legajo);
            }else if(strlen(cursor->estudiante.nombre) < 19){
                printf("%i.  %s     ", contador, cursor->estudiante.nombre);
                for(int i=strlen(cursor->estudiante.nombre); i<19; i++){
                    printf(" ");
                }
                printf("%d     %d\n", cursor->estudiante.edad, cursor->estudiante.legajo);
            }else{
                printf("%i.  %s", contador, cursor->estudiante.nombre);
                for(int i=strlen(cursor->estudiante.nombre); i<24; i++){
                    printf(" ");
                }
                printf("%d     %d\n", cursor->estudiante.edad, cursor->estudiante.legajo);
            }
            cursor = cursor->proximo;
            if(contador == 5 || cursor == NULL){
                contadorTotal = contadorTotal + contador;
                printf("\nPagina anterior / Pagina siguiente / Elegir Pagina Actual (A/S/E): ");
                char opcion;
                scanf("%s", &opcion);
                printf("\n");
                fflush(stdin);
                switch (opcion){
                    case 'S':
                        contador = 0;
                        break;
                    case 's':
                        contador = 0;
                        break;
                    case 'A':
                        cursor = lista;
                        if(contadorTotal % 5 == 0){
                            for(int i=0; i<contadorTotal-10; i++){
                                cursor = cursor->proximo;
                            }                            
                            contadorTotal = contadorTotal-10;
                        }else{
                            for(int i=0; i<contadorTotal-(5+contador); i++){
                                cursor = cursor->proximo;
                            }
                            contadorTotal = contadorTotal - (10-(5-contador));
                        } 
                        
                        contador = 0;
                        break;
                    case 'a':
                        cursor = lista;
                        if(contadorTotal % 5 == 0){
                            for(int i=0; i<contadorTotal-10; i++){
                                cursor = cursor->proximo;
                            }                            
                            contadorTotal = contadorTotal-10;
                        }else{
                            for(int i=0; i<contadorTotal-(5+contador); i++){
                                cursor = cursor->proximo;
                            }
                            contadorTotal = contadorTotal - (10-(5-contador));
                        } 
                        
                        contador = 0;
                        break;
                    case 'E':
                        break;
                    case 'e':
                        break;
                    default:
                        break;
                }
            }
        }
        printf("\n");
    }
}