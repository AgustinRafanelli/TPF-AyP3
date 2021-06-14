#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructura_estudiantes.c"


void darDeAlta(NodoEstudiante *lista, Estudiante estudianteActual){
    printf("**************************************************\n");
    printf("            ALTA DE ESTUDIANTES\n");
    printf("\n");
    printf("Ingrese el nombre del estudiante: ");
    
    char nombre[64];
    scanf("%s[^\n]", &nombre);

    printf("Ingrese edad: ");
    int edad;
    scanf("%d", &edad);
    lista = altaEstudiante(nombre, edad, lista);

    printf("\n Estudiante agregado con exito\n\n");
}

void buscarEstudinte(NodoEstudiante *lista, Estudiante estudianteActual){
    printf("Ingrese el nombre del estudiante: ");
    char nombre[64];
    scanf("%s[^\n]", nombre);
    imprimirLista(obtenerEstudiante(lista, nombre));

}

void buscarEstudianteEdad(NodoEstudiante *lista, Estudiante estudianteActual){  

    int min;
    int max;
    printf("Ingrese edad minima: ");
    scanf("%i", min);
    printf("Ingrese edad maxima: ");
    scanf("%i", max);
    printf("minima: %i\nmaxima: %i\n",min,max);
    imprimirLista(obtenerEstudiantesPorEdad(lista, min, max));

}

void iniciarSistema(NodoEstudiante *lista, Estudiante estudianteActual){
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
    int opcion = 50;
    scanf("%i", &opcion);

    switch (opcion)
    {
    case 1:
        imprimirLista(lista);
        iniciarSistema(lista, estudianteActual);
        break;

    case 2:
        darDeAlta(lista, estudianteActual);
        iniciarSistema(lista, estudianteActual);
        break;

    case 3:
        buscarEstudinte(lista, estudianteActual);
        break;

    case 4:
        buscarEstudianteEdad(lista, estudianteActual);
        break;
    
    case 0:
        printf("Se sale");
        break;

    default:
        printf("Seleccione una opcion valida\n\n");
        iniciarSistema(lista, estudianteActual);
        break;
    }
}


int main() {
    NodoEstudiante *lista = crearLista();
    Estudiante estudianteActual;
    lista = altaEstudiante("Juan Roman Riquelme", 30, lista);
    lista = altaEstudiante("Carlos Saul Menem", 50, lista);
    lista = altaEstudiante("Leopoldo Garcia", 38, lista);
    lista = altaEstudiante("Marcos Galperin", 35, lista);
    imprimirLista(lista);
/*
    
    imprimirLista(obtenerEstudiantesPorEdad(lista, min, max));
    */
    iniciarSistema(lista, estudianteActual);

    /*
    imprimirLista(lista);
    NodoEstudiante *lista2 = crearLista();
    lista2 = obtenerEstudiantesPorEdad(lista, 30, 40);
    imprimirLista(lista2);

    Materia analisis;
    analisis.titulo = "Analisis 1";
    analisis.aprobada = false;
    analisis.cursando = true;
   /*
    Estudiante estudianteActual = obtenerEstudiante(lista, "Juan Roman Riquelme");
    estudianteActual.materias = agregarMateria(estudianteActual.materias, analisis);
    imprimirListaMaterias(estudianteActual.materias); 

    /*
    NodoMateria *listaMaterias = crearListaMaterias();
    listaMaterias = agregarMateria(listaMaterias, analisis);
    imprimirListaMaterias(listaMaterias);
    */

}