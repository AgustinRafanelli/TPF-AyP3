#include "estructuras.c"

Nodo *lista;

void altaEstudiante(char *nombre, int legajo){
    Estudiante estudiante;
    estudiante.nombre = nombre;
    estudiante.legajo = legajo;
    //Se agrega el alumno a la lista
    lista = agregarElemento(lista, estudiante);
}

void iniciarSistema(){
    //Se crea la lista
    lista = crearLista();
}

void imprimir(){
    imprimirLista(lista);
}



int main() {
    iniciarSistema();
    altaEstudiante("Juan Roman Riquelme", 15632);
    altaEstudiante("Carlos Saul Menem", 25556);
    altaEstudiante("Marcos Galperin", 11123);
    imprimir();
}