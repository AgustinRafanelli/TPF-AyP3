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
    int correlativas[2];
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

bool verificarCorrelativas(Materia materia, NodoMateria *listaDelAlumno){
    bool cumple = false;
    if(listaDelAlumno == NULL && materia.correlativas[0] == 0 && materia.correlativas[1] == 0){
        return true;
    } else{
        NodoMateria *cursor = listaDelAlumno;
        while(cursor != NULL){
            for(int i = 0; i < 2; i++){
                if(materia.correlativas[i] == cursor->materia.codigo || materia.correlativas[i] == 0){
                    cumple = true;
                }else cumple = false;
            }
            cursor = cursor->proximo;
        }
        return cumple;
    }
}

NodoMateria *altaMateria(char *titulo, NodoMateria *lista, int correlativa1, int correlativa2){
    if(verificarRepeticion(lista, titulo) == false){
        Materia materia;
        strcpy(materia.titulo, titulo);
        materia.aprobada = false;
        materia.cursando = true;
        materia.notaFinal = 0;
        materia.correlativas[0] = correlativa1;
        materia.correlativas[1] = correlativa2;
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

void eliminarMateria (NodoMateria *lista, int codigo){
    NodoMateria *proximo;
    NodoMateria *cursor = lista;
    if(lista == NULL){
        return;
    } else if(cursor->materia.codigo == codigo){
        proximo = cursor->proximo;
        free(cursor);
        cursor = proximo;
    }else{
        while (cursor->proximo != NULL && cursor->proximo->materia.codigo != codigo) {
            cursor = cursor->proximo;
        }
        if(cursor->proximo->proximo == NULL && cursor->proximo->materia.codigo == codigo){
            proximo = cursor->proximo;
            free(cursor);
            cursor = proximo;
        }else if(cursor->proximo->materia.codigo == codigo){
            proximo = cursor->proximo->proximo;
            free(cursor->proximo);
            cursor->proximo = proximo;
        }
    }
}

void imprimirListaMaterias(NodoMateria *lista){
    if(lista == NULL){
        printf("La lista esta vacia\n");
    }else{
        NodoMateria *cursor = lista;
        int contador = 0;
        int contadorTotal = 0;
        printf("\n    Titulo                                 Codigo\n\n");
        while (cursor != NULL && contador < 5) {
            contador = contador + 1;
            contadorTotal = contadorTotal + 1;
            if(strlen(cursor->materia.titulo) == 10){
                printf("%i.  %s                               %d\n", contador, cursor->materia.titulo, cursor->materia.codigo);
            }else if(strlen(cursor->materia.titulo) >= 27){
                printf("%i.  %s", contador, cursor->materia.titulo);
                for(int i=27-(strlen(cursor->materia.titulo)-27); i>13; i--){
                    printf(" ");
                }
                printf("%d\n", cursor->materia.codigo);
            }else if(strlen(cursor->materia.titulo) < 10){
                printf("%i.  %s                               ", contador, cursor->materia.titulo);
                for(int i=strlen(cursor->materia.titulo); i<10; i++){
                    printf(" ");
                }
                printf("%d\n", cursor->materia.codigo);
            }else{
                printf("%i.  %s", contador, cursor->materia.titulo);
                for(int i=strlen(cursor->materia.titulo); i<41; i++){
                    printf(" ");
                }
                printf("%d\n", cursor->materia.codigo);
            }
            
            cursor = cursor->proximo;
            if(contador == 5 || cursor == NULL){
                printf("\nPagina anterior / Pagina siguiente (A/S): ");
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
                        contador = 0;
                        cursor = lista;
                        contadorTotal = contadorTotal-5;
                        for(int i=0; i<contadorTotal-10; i++){
                            cursor = cursor->proximo;
                        }
                        break;
                    case 'a':
                        contador = 0;
                        cursor = lista;
                        contadorTotal = contadorTotal-5;
                        for(int i=0; i<contadorTotal-10; i++){
                            cursor = cursor->proximo;
                        }
                        break;
                    default:
                        break;
                }
            } 
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
        int contadorTotal = 0;
        printf("\n       Titulo                      Nota   Codigo  Cursando  Aprobada  Correlativa de\n\n");
        while (cursor != NULL && contador < 5) {
            contador = contador + 1;
            contadorTotal = contadorTotal + 1;
            char *aprobada;
            char *cursando;
            if(cursor->materia.aprobada == false){aprobada = "No";} else{ aprobada = "Si";}
            if(cursor->materia.cursando == false){cursando = "No";} else{ cursando = "Si";}
            if(strlen(cursor->materia.titulo) == 10){
                printf("%i.  %s                     %d       %d        %s        %s          %i y %i\n", contador, cursor->materia.titulo, cursor->materia.notaFinal, cursor->materia.codigo, cursando, aprobada,  cursor->materia.correlativas[0], cursor->materia.correlativas[1]);
            }else if(strlen(cursor->materia.titulo) >= 27){
                printf("%i.  %s", contador, cursor->materia.titulo);
                for(int i=27-(strlen(cursor->materia.titulo)-27); i>23; i--){
                    printf(" ");
                }
                printf("%d       %d        %s        %s          %i y %i\n", cursor->materia.notaFinal, cursor->materia.codigo, cursando, aprobada,  cursor->materia.correlativas[0], cursor->materia.correlativas[1]);
            }else if(strlen(cursor->materia.titulo) < 10){
                printf("%i.  %s                     ", contador, cursor->materia.titulo);
                for(int i=strlen(cursor->materia.titulo); i<10; i++){
                    printf(" ");
                }
                printf("%d       %d        %s        %s          %i y %i\n", cursor->materia.notaFinal, cursor->materia.codigo, cursando, aprobada,  cursor->materia.correlativas[0], cursor->materia.correlativas[1]);
            }else{
                printf("%i.  %s", contador, cursor->materia.titulo);
                for(int i=27-(strlen(cursor->materia.titulo)-27); i>23; i--){
                    printf(" ");
                }
                printf("%d       %d        %s        %s          %i y %i\n", cursor->materia.notaFinal, cursor->materia.codigo, cursando, aprobada,  cursor->materia.correlativas[0], cursor->materia.correlativas[1]);
            }
            cursor = cursor->proximo;
            if(contador == 5 || cursor == NULL){
                printf("\nPagina anterior / Pagina siguiente (A/S): ");
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
                        contador = 0;
                        cursor = lista;
                        contadorTotal = contadorTotal-5;
                        for(int i=0; i<contadorTotal-10; i++){
                            cursor = cursor->proximo;
                        }
                        break;
                    case 'a':
                        contador = 0;
                        cursor = lista;
                        contadorTotal = contadorTotal-5;
                        for(int i=0; i<contadorTotal-10; i++){
                            cursor = cursor->proximo;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        printf("\n");
    }
}