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
#include "Libs/TimeTable.h"


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
            printf ("SERVER > VISUALIZAR HORARIO\n");
            PrintTimeTable (tt);
            pause ();
            input = '0';
        }
        if (input == '2'){
            clearscr ();
            printf ("SERVER > EDITAR HORARIO\n");
            keys = tt [0];
            list = keys [0];
            pushBack (list,createClass());
        }
    }
    return EXIT_SUCCESS;
}
