#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "estructura_estudiantes.c"


void darDeAlta(NodoEstudiante *lista){
    printf("**************************************************\n");
    printf("            ALTA DE ESTUDIANTES\n");
    printf("\n");
    printf("Ingrese el nombre del estudiante: ");
    
    char nombre[64];
    fflush(stdin);
    scanf("%[^\n]", &nombre);
    printf("Ingrese edad: ");
    int edad;
    scanf("%i", &edad);
    fflush(stdin);
    lista = altaEstudiante(nombre, edad, lista);

    printf("\n Estudiante agregado con exito\n\n");
}
void modificarEstudiante(Estudiante estudiante, NodoMateria *listaMaterias){
        printf("**************************************************\n");
    printf("            MODIFICACION DE ESTUDIANTE\n");
    printf("            %s (%i)\n", estudiante.nombre, estudiante.edad);
    printf("\n");
    printf("1.Lista de Materias\n");
    printf("2.Anotarse en una materia\n");
    printf("3.Rendir en una materia\n");
    int opcion;
    scanf("%i", &opcion);
    fflush(stdin);
    switch (opcion)
    {
        case 1:
            imprimirListaMaterias(estudiante.materias);
            modificarEstudiante(estudiante, listaMaterias);
            break;

        case 2:
            // Falta obtener la materia deseada, le estoy asignando arbitrariamente la primera para probar
            estudiante.materias = agregarMateria(estudiante.materias, listaMaterias->materia);
            modificarEstudiante(estudiante, listaMaterias);
            break;

        /*case 3:
            modificarEstudiante(estudiante, listaMaterias);
            break;*/

        default:
            printf("Seleccione una opcion valida\n\n");
            modificarEstudiante(estudiante, listaMaterias);
            break;
    }
}
void seleccionarEstudiante(NodoEstudiante *lista, NodoMateria *listaMaterias){
    int legajo;
    printf("Ingrese legajo: ");
    scanf("%i", &legajo);
    printf("\n");
    fflush(stdin);
    Estudiante estudiante = obtenerEstudianteActual(lista, legajo);
    if(estudiante.legajo != legajo){
        printf("Legajo no encontrado\n");
        seleccionarEstudiante(lista, listaMaterias);
    }else modificarEstudiante(estudiante, listaMaterias);
}

void buscarEstudiante(NodoEstudiante *lista, NodoMateria *listaMaterias){
    printf("Ingrese el nombre del estudiante: ");
    char nombre[64];
    scanf("%[^\n]", nombre);
    fflush(stdin);
    NodoEstudiante *listaObtenida = obtenerEstudiante(lista, nombre);
    imprimirLista(listaObtenida);
    seleccionarEstudiante(listaObtenida, listaMaterias);
}

void buscarEstudianteEdad(NodoEstudiante *lista, NodoMateria *listaMaterias){
    int min;
    int max;
    printf("Ingrese edad minima: ");
    scanf("%d[^\n]", &min);
    fflush(stdin);
    printf("Ingrese edad maxima: ");
    scanf("%d[^\n]", &max);
    fflush(stdin);
    NodoEstudiante *listaObtenida = obtenerEstudiantesPorEdad(lista, min, max);
    imprimirLista(listaObtenida);
    seleccionarEstudiante(listaObtenida, listaMaterias);

}

void iniciarSistema(NodoEstudiante *lista, NodoMateria *listaMaterias){
    printf("**************************************************\n");
    printf("     BIENVENIDO AL SISTEMA DE ESTUDIANTES\n");
    printf("\n");
    printf("1.Lista de estudiantes\n");
    printf("2.Dar de alta estudiante\n");
    printf("3.Buscar por nombre\n");
    printf("4.Buscar por rango de edad\n");
    printf("\n");
    printf("0.Exit\n");
    printf("*************************************************\n\n");
    int opcion;
    scanf("%i", &opcion);
    fflush(stdin);

    switch (opcion)
    {
    case 1:
        imprimirLista(lista);
        iniciarSistema(lista, listaMaterias);
        break;

    case 2:
        darDeAlta(lista);
        iniciarSistema(lista, listaMaterias);
        break;

    case 3:
        buscarEstudiante(lista, listaMaterias);
        iniciarSistema(lista, listaMaterias);
        break;

    case 4:
        buscarEstudianteEdad(lista, listaMaterias);
        iniciarSistema(lista, listaMaterias);
        break;
    
    case 0:
        printf("Se sale");
        break;

    default:
        printf("Seleccione una opcion valida\n\n");
        iniciarSistema(lista, listaMaterias);
        break;
    }
}


int main() {
    NodoEstudiante *lista = crearLista();
    lista = altaEstudiante("Juan Roman Riquelme", 30, lista);
    lista = altaEstudiante("Carlos Saul Menem", 50, lista);
    lista = altaEstudiante("Leopoldo Garcia", 38, lista);
    lista = altaEstudiante("Marcos Galperin", 35, lista);
    NodoMateria *listaMaterias = crearListaMaterias();
    listaMaterias = altaMateria("Analisis I", listaMaterias);
    listaMaterias = altaMateria("Algebra I", listaMaterias);
    listaMaterias = altaMateria("Algoritmos y Programacion I", listaMaterias);
    iniciarSistema(lista, listaMaterias);
}