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
    char input;
    while (1){
        clearscr ();
        printf ("SERVER > MENU PRINCIPAL\n\n1.Ver & Editar Horario Institucional\n3.Salir\n\nInput: $ ");
        input = getchar ();
        if (input == '1'){
            clearstdin ();
            while (input != '4'){
                clearscr ();
                printf ("SERVER > VISUALIZAR HORARIO\n");
                PrintTimeTable (tt);
                printf ("\n");
                input = '0';
                while (input != '1' && input != '4' && input != '3' && input != '2') {
                    printf ("1. Ver clave en detalle 2. Agreagar 3. Eliminar 4. Volver\nInput : $ ");
                    input = getchar ();
                    clearstdin ();
                }
                if (input == '1') {
                    SeeKey (tt);
                    pause ();
                }
                if (input == '2') AddClass (tt);
                if (input == '3') {Remove (tt); clearstdin();}
            }
            input = '0';
        }
        if(input == '3'){
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}
