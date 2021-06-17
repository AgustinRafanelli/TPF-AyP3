#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "estructura_estudiantes.c"


void darDeAltaEstudiante(NodoEstudiante *lista){
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

void darDeAltaMateria(NodoMateria *lista){
    printf("**************************************************\n");
    printf("            ALTA DE MATERIAS\n");
    printf("\n");
    printf("Ingrese el titulo de la materia: ");
    char titulo[64];
    scanf("%[^\n]", &titulo);
    fflush(stdin);
    int correlativa1, correlativa2;
    printf("Ingrese correlativa N 1 (0 si no tiene): ");
    scanf("%i", &correlativa1);
    fflush(stdin);
    printf("Ingrese correlativa N 2 (0 si no tiene): ");
    scanf("%i", &correlativa2);
    fflush(stdin);
    lista = altaMateria(titulo, lista, correlativa1, correlativa2);
    printf("\n Materia dada de alta exitosamente\n\n");
}

void darDeBajaMateria(NodoMateria *lista){
    printf("**************************************************\n");
    printf("            BAJA DE MATERIAS\n");
    printf("\n");
    printf("Ingrese el codigo de la materia: ");
    int codigo;
    scanf("%i", &codigo);
    fflush(stdin);
    if(eliminarMateria(lista, codigo) == true) printf("\n Materia dada de baja exitosamente\n\n");
    else printf("\n No existe una materia con ese codigo\n\n");
}

Materia seleccionarMateria(Estudiante estudiante, NodoMateria *listaMaterias){
    Materia materia;
    int codigo;
    while(materia.codigo != codigo){
        printf("Ingrese el codigo de la materia: ");
        scanf("%i", &codigo);
        printf("\n");
        fflush(stdin);
        materia = obtenerMateria(listaMaterias, codigo);
        if(materia.codigo != codigo){
            printf("Materia no encontrada\n");
        }
    }
    return materia;
}

NodoMateria *rendirMateria(int codigo, NodoMateria *listaMaterias){
    int nota = 0;
    while(nota < 1 || nota > 10){
        printf("Ingrese la nota obtenida: ");
        scanf("%d", &nota);
        printf("\n");
        fflush(stdin);
        if(nota < 1 || nota > 10){
            printf("Solo se permiten notas del 1 al 10\n");
        }
    }
    listaMaterias = rendir(listaMaterias, codigo, nota);
    printf("Nota registrada con exito\n");
    return listaMaterias;
}

NodoEstudiante *modificarEstudiante(NodoEstudiante *lista, NodoMateria *listaMaterias, int legajo){
    NodoEstudiante *estudiante = modificarEstudianteActual(lista, legajo);
    printf("**************************************************\n");
    printf("            MODIFICACION DE ESTUDIANTE\n");
    printf("            %s (%i)\n", estudiante->estudiante.nombre, estudiante->estudiante.edad);
    printf("\n");
    printf("1.Lista de Materias\n");
    printf("2.Anotarse en una materia\n");
    printf("3.Rendir una materia\n");
    printf("4 Volver al menu principal\n");
    int opcion;
    scanf("%i", &opcion);
    fflush(stdin);
    Materia materia;
    switch (opcion)
    {
        case 1:
            imprimirMateriasDelAlumno(estudiante->estudiante.materias);
            modificarEstudiante(lista, listaMaterias, legajo);
            break;

        case 2:
            materia = seleccionarMateria(estudiante->estudiante, listaMaterias);
            if(verificarCorrelativas(materia, estudiante->estudiante.materias) == true){
                if(materia.habilitada == true){
                    estudiante->estudiante.materias = agregarMateria(estudiante->estudiante.materias, materia);
                    printf("Inscripto con exito a la materia: %s\n", materia.titulo);
                }else printf("No se pudo inscribir a la materia (la materia fue dada de baja)\n");
                
            }else printf("No se pudo inscribir a la materia (no cumple con las correlativas)\n");
            modificarEstudiante(lista, listaMaterias, legajo);
            break;

        case 3:
            materia = seleccionarMateria(estudiante->estudiante, estudiante->estudiante.materias);
            estudiante->estudiante.materias = rendirMateria(materia.codigo, estudiante->estudiante.materias);
            modificarEstudiante(lista, listaMaterias, legajo);
            break;

        case 4:
            return estudiante;
            break;

        default:
            printf("Seleccione una opcion valida\n\n");
            modificarEstudiante(lista, listaMaterias, legajo);
            break;
    }
}

NodoEstudiante *seleccionarEstudiante(NodoEstudiante *lista, NodoMateria *listaMaterias){
    int legajo;
    printf("Ingrese legajo: ");
    scanf("%i", &legajo);
    printf("\n");
    fflush(stdin);
    if(verificarEstudiante(lista, legajo) == false){
        printf("Legajo no encontrado\n");
        seleccionarEstudiante(lista, listaMaterias);
    }else{
        return modificarEstudiante(lista, listaMaterias, legajo);
    }
}

NodoEstudiante *buscarEstudiante(NodoEstudiante *lista, NodoMateria *listaMaterias){
    printf("Ingrese el nombre del estudiante: ");
    char nombre[64];
    scanf("%[^\n]", nombre);
    fflush(stdin);
    NodoEstudiante *listaObtenida = obtenerEstudiante(lista, nombre);
    imprimirLista(listaObtenida);
    return seleccionarEstudiante(listaObtenida, listaMaterias);
}

NodoEstudiante *buscarEstudianteEdad(NodoEstudiante *lista, NodoMateria *listaMaterias){
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
    return seleccionarEstudiante(listaObtenida, listaMaterias);

}

NodoEstudiante *modificarEstudiantes(NodoEstudiante *lista, NodoMateria *listaMaterias){
    printf("**************************************************\n");
    printf("             MODIFICACION DE ESTUDIANTES          \n");
    printf("\n");
    printf("1.Lista de estudiantes\n");
    printf("2.Dar de alta estudiante\n");
    printf("3.Buscar por nombre\n");
    printf("4.Buscar por rango de edad\n");
    printf("\n");
    printf("0.Volver al menu principal\n");
    printf("*************************************************\n\n");
    int opcion;
    scanf("%i", &opcion);
    fflush(stdin);
    switch (opcion){
        case 1:
            imprimirLista(lista);
            modificarEstudiantes(lista, listaMaterias);
            break;

        case 2:
            darDeAltaEstudiante(lista);
            modificarEstudiantes(lista, listaMaterias);
            break;

        case 3:
            lista = buscarEstudiante(lista, listaMaterias);
            modificarEstudiantes(lista, listaMaterias);
            break;

        case 4:
            lista = buscarEstudianteEdad(lista, listaMaterias);
            modificarEstudiantes(lista, listaMaterias);
            break;
        
        case 0:
            return lista;
            break;

        default:
            printf("Seleccione una opcion valida\n\n");
            modificarEstudiantes(lista, listaMaterias);
            break;
    }
}

void modificarMaterias(NodoMateria *listaMaterias){
    printf("**************************************************\n");
    printf("             MODIFICACION DE MATERIAS          \n");
    printf("\n");
    printf("1.Lista de materias\n");
    printf("2.Dar de alta materia\n");
    printf("3.Dar de baja materia\n");
    printf("\n");
    printf("0.Volver al menu principal\n");
    printf("*************************************************\n\n");
    int opcion;
    scanf("%i", &opcion);
    fflush(stdin);
    switch (opcion){
        case 1:
            imprimirListaMaterias(listaMaterias);
            modificarMaterias(listaMaterias);
            break;

        case 2:
            darDeAltaMateria(listaMaterias);
            modificarMaterias(listaMaterias);
            break;
        
        case 3:
            darDeBajaMateria(listaMaterias);
            modificarMaterias(listaMaterias);
            break;

        case 0:
            break;

        default:
            printf("Seleccione una opcion valida\n\n");
            modificarMaterias(listaMaterias);
            break;
    }    
}

void iniciarSistema(NodoEstudiante *lista, NodoMateria *listaMaterias){
    printf("**************************************************\n");
    printf("     BIENVENIDO AL SISTEMA DE ESTUDIANTES\n");
    printf("\n");
    printf("1.Modificar estudiantes\n");
    printf("2.Modificar materias\n");
    printf("\n");
    printf("0.Exit\n");
    printf("*************************************************\n\n");
    int opcion;
    scanf("%i", &opcion);
    fflush(stdin);
    switch(opcion){
        case 1:
            lista = modificarEstudiantes(lista, listaMaterias);
            iniciarSistema(lista, listaMaterias);
            break;

        case 2:
            modificarMaterias(listaMaterias);
            iniciarSistema(lista, listaMaterias);
            break;

        case 0:
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
    listaMaterias = altaMateria("Analisis I", listaMaterias, 0, 0);
    listaMaterias = altaMateria("Algebra I", listaMaterias, 0, 0);
    listaMaterias = altaMateria("Algoritmos y Programacion I", listaMaterias, 0, 0);
    //listaMaterias = altaMateria("Analisis II", listaMaterias, 1, 2);
    iniciarSistema(lista, listaMaterias);
}