/* PROYECTO DE TITULO @ESTRUCTURA
 * Este programa es capazas de gestonar de manera rapida y eficinete
 * los horarios de un estudiante y vincularlos con los eventos y actividades
 * de su institucion.
 * DESARROLLADO POR: Felipe Bustos, Rodrigo Maureira, Rodrigo Vilches
 * CURSO: Estructura de Datos S1, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Libs/List.h"
#include "Libs/mauri.h"

                            // Definiciones para gestionar la semana
#define t_keys 7            // Claves de las que se compone un día
#define t_days 7            // Total de días hábiles de la semana

typedef struct {            // Estrucuta para añadir una clase
    char *name;             // Nombre de la clase
    char *location;         // Ubicacion de la clase
} Class;                    // Nombre de la estructura

Class* createClass (){                      // Procedimiento para crear una clase
    getchar ();                             // Limpia el buffer
    Class *c = malloc (sizeof (Class));     // Reserva espacio
    c -> name = readString ();              // Nombre de la asignatura?
    c -> location = readString ();          // Ubicacion
    return c;                               // Retorna el curso
}

void** CreateKeys (){                                           // Procedimiento para crea las claves de las que se compone un dia
    int k;                                                      // Variable para moverse a traves de las claves
    void** Keys = (void**) malloc (sizeof (void*)*t_keys);      // Reserva espacio para las claves
    for (k = 0; k < t_keys; k ++) Keys [k] = createList();      // Cada clave requiere de una lista de actividades asociada
    return Keys;                                                // Retornamos el conjunto de claves
}

void** NewTimeTable (){                                         // Procedimiento para crear la semana en su conjunto
    int d;                                                      // Variable para recorrer los dias
    void** Days = (void**) malloc (sizeof(void*)*t_days);       // Generamos los dias habiles de trabajo
    for (d = 0; d < t_days; d ++) Days[d] = CreateKeys ();      // Cada dia esta conformado por claves
    return Days;                                                // retornamos la semana creada
}

void PrintTimeTable (void** tt){    // Procedimiento para imprimir la semana por pantalla
    int d,k;                        // Variables para recorrer los dias (d) y las claves (k)
    void** Keys = NULL;             // Variable para almacenar las claves de un dia
    List* list = NULL;              // Variable para almacenar la lista de actividades para la clave, si creo que esta demas
    Class *c;                       // Variable para almacenar un curso (sacado de la lista)
    for (d = 0; d < t_days; d ++){              // Reocrremos los dias
        NumbToDay(d + 1);                       // Imprimimos el nombre del dia
        printf (":\n");                         // Hacemos que quede un poco mas bonito
        Keys = tt [d];                          // Montamos las claves del dia
        for (k = 0; k < t_keys; k ++){          // Recorremos las claves del dia
            list = Keys [k];                    // Montamos la lista de actividades de cada clave
            c = first (list);                   // Rescatamos el primer elemento de la lita de actividades
            while (c){                          // Si existe
                printf ("%s\n", c -> name);     // Imprimimos su nombre
                c = next (list);                // Rescatamos el siguient elemento de la lista y repetimso el proceso
            }
        }
    }
}

int main()
{
    void** tt = NewTimeTable ();
    void** keys = NULL;
    List* list = NULL;
    char input;
    while (1){
        clearscr ();
        printf ("SERVER > MENU PRINCIPAL\n1.Ver horario\n2.Editar horario\n\nInput: $ ");
        input = getchar ();
        if (input == '1'){
            clearscr ();
            PrintTimeTable (tt);
            pause ();
        }
        if (input == '2'){
            keys = tt [0];
            list = keys [0];
            pushBack (list,createClass());
        }
    }
    return EXIT_SUCCESS;
}
