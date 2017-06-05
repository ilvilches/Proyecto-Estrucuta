#ifndef TIMETABLE_H_INCLUDED
#define TIMETABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "mauri.h"
#include "TimeTable.h"

#define t_keys 7                // Claves de las que se compone un día
#define t_days 7                // Total de días hábiles de la semana

typedef struct {                // Estrucuta para añadir una clase
    char name [50];                 // Nombre de la clase
    char location [10];             // Ubicacion de la clase
    char *time;                 // Hora de inicio de la actividad
    int type;                   // Tipo de act (0 = clase, 1 = buses, 2 = caf, 3 = limpieza, 4 = suspension)
} Class;                        // Nombre de la estructura

Class* createClass ();          // Procedimiento para crear una clase
void** CreateKeys ();           // Procedimiento para crear las claves de las que se compone un dia
void** NewTimeTable ();         // Procedimiento para crear la semana en su conjunto
void PrintTimeTable (void**);   // Procedimiento para imprimir la semana por pantalla
void AddClass (void**);         // Procedimiento para añadir una actividad a una clave
void SeeKey (void**);           // Procedimiento para ver una clave en detalle
void Remove (void**);           // Procedimiento para eliminar un item (independiente de 'c -> type') de una lista

#endif // TIMETABLE_H_INCLUDED
