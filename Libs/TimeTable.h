#ifndef TIMETABLE_H_INCLUDED
#define TIMETABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "mauri.h"
#include "TimeTable.h"

                                // Definiciones para gestionar la semana
#define t_keys 7                // Claves de las que se compone un día
#define t_days 5                // Total de días hábiles de la semana

typedef struct {                // Estrucuta para añadir una clase
    char *name;                 // Nombre de la clase
    char *location;             // Ubicacion de la clase
} Class;                        // Nombre de la estructura

Class* createClass ();          // Procedimiento para crear una clase
void** CreateKeys ();           // Procedimiento para crea las claves de las que se compone un dia
void** NewTimeTable ();         // Procedimiento para crear la semana en su conjunto
void PrintTimeTable (void**);   // Procedimiento para imprimir la semana por pantalla
void Add (void**);              // Procedimiento para añadir una actividad a una clave

#endif // TIMETABLE_H_INCLUDED
