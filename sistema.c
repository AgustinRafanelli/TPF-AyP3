#include "estructura_estudiantes.c"


Nodo *altaEstudiante(char *nombre, int edad, Nodo *lista){
    Estudiante estudiante;
    estudiante.nombre = nombre;
    estudiante.edad = edad;
    //Se agrega el alumno a la lista
    lista = agregarElemento(lista, estudiante);
    return lista;
}

void iniciarSistema(Nodo *lista){
    
}

int main() {
    Nodo *lista;
    lista = crearLista();
    lista = altaEstudiante("Juan Roman Riquelme", 30, lista);
    lista = altaEstudiante("Carlos Saul Menem", 50, lista);
    lista = altaEstudiante("Marcos Galperin", 35, lista);
    lista = altaEstudiante("Leopoldo Garcia", 38, lista);
    imprimirLista(lista);
}