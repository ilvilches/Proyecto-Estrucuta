#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "mauri.h"
#include "TimeTable.h"

void NkTab (int nk){                                                // Procedimiento para tabular
    if (nk < 8) printf ("      ");                                  // creará un pequeño intento de compaginado
    if (nk == 8) printf ("     ");                                  // que conciste en crear un pequeño tabulado al saltarse especios de acuerdo
    if (nk > 8) printf ("    ");                                    // a la clave que se esté analizando, soporta un maximo de 49 claves diarias
}
Class* createClass (){                                              // Procedimiento para crear una clase
    Class *c = malloc (sizeof (Class));                             // Reserva espacio
    printf ("\nNombre? : ");                                        // Pregunta por el nombre
    mgets (c -> name, 50);                                          // Guarda el nombre (incluir espacio para '\0' y '\n')
    printf ("Donde?  : ");                                          // Pregunta por la clave
    mgets (c -> location, 10);                                      // Guarda la clave
    c -> type = 0;                                                  // Esto será una clase (type = 0)
    return c;                                                       // Retorna el curso
}
void** CreateKeys (){                                               // Procedimiento para crea las claves de las que se compone un dia
    int k;                                                          // Variable para moverse a traves de las claves
    void** Keys = (void**) malloc (sizeof (void*)*t_keys);          // Reserva espacio para las claves
    for (k = 0; k < t_keys; k ++) Keys [k] = createList();          // Cada clave requiere de una lista de actividades asociada
    return Keys;                                                    // Retornamos el conjunto de claves
}
void** NewTimeTable (){                                             // Procedimiento para crear la semana en su conjunto
    int d;                                                          // Variable para recorrer los dias
    void** Days = (void**) malloc (sizeof(void*)*t_days);           // Generamos los dias habiles de trabajo
    for (d = 0; d < t_days; d ++) Days[d] = CreateKeys ();          // Cada dia esta conformado por claves
    return Days;                                                    // retornamos la semana creada
}
void PrintTimeTable (void** tt){                                    // Procedimiento para imprimir la semana por pantalla
    int d, k, nk;                                                   // Variables para recorrer los dias (d) y las claves (k), nk es el numero de la clave (ej: 1-2, 3-4, ..., 13-14)
    void** Keys = NULL;                                             // Variable para almacenar las claves de un dia
    List* list = NULL;                                              // Variable para almacenar la lista de actividades para la clave, si creo que esta demas
    Class *c;                                                       // Variable para almacenar un curso (sacado de la lista)
    for (d = 0; d < t_days; d ++){                                  // Reocrremos los dias
        printf ("\n");                                              // Saltamos una linea
        NumbToDay(d + 1);                                           // Imprimimos el nombre del dia
        printf (":\n");                                             // Hacemos que quede un poco mas bonito
        Keys = tt [d];                                              // Montamos las claves del dia
        nk = 0;                                                     // Inicializamos nk en 0
        for (k = 0; k < t_keys; k ++, nk += 2){                     // Recorremos las claves del dia
            list = Keys [k];                                        // Montamos la lista de actividades de cada clave
            c = first (list);                                       // Rescatamos el primer elemento de la lita de actividades
            printf ("Clave: %d-%d", nk+1, nk+2);                    // Imprimimos la clave atual
            if (!c) printf ("\n");                                  // Si no hay elementos en la lista, se salta una linea
            else NkTab (nk);                                        // Si hay elementos llama a NkTab para crear un compaginado
            while (c){                                              // Si existe
                printf (" [%s] ", c -> location);                   // Imprimimos su ubicacion
                printf ("%s", c -> name);                           // Imprimimos su nombre
                c = next (list);                                    // Rescatamos el siguient elemento de la lista y repetimso el proceso
                if (c) printf (",");                                // Si aun quedan elementos por mostrar, imprime una como ','
                else printf ("\n");                                 // En caso contrario termina la linea
            }
        }
    }
}
List *MountKey (void** tt){                                         // Procedimiento para rescatar una lista de una clave de un dia
    int d = -1,k = -1;                                              // Variables para montar el dia y la clave
    char day [10],key[6];                                           // Variables para interactuar con el usuario
    void** keys = NULL;                                             // Variable para montar las claves
    while (d < 0 || d >= t_days) {                                  // Ciclo para preguntar por el dia
        printf ("Dia?   :  ");                                      // Preguntamos por el dia
        scanf ("%s", day);                                          // Guardamos el dia
        if (strstr (str_tolower (day), "lunes")) d = 0;             // Vemos que a que dia corresponde
        else if (strstr (str_tolower (day), "martes")) d = 1;       // Por defecto son 7
        else if (strstr (str_tolower (day), "miercoles")) d = 2;    // Pero solamente validará la respuesta
        else if (strstr (str_tolower (day), "jueves")) d = 3;       // cuando el día este dentro del rango de
        else if (strstr (str_tolower (day), "viernes")) d = 4;      // dias habiles (t_days)
        else if (strstr (str_tolower (day), "sabado")) d = 5;       // De momento concideramos como dias
        else if (strstr (str_tolower (day), "domingo")) d = 6;      // Habiles 5 (Lunes a Viernes)
        else{                                                       // Si no encuentra el concordancias
        printf ("%s < no se reconoce como dia valido\n", day);      // Señala que el dia ingresado no es valido
        clearstdin ();}                                             // Y limpiamos el buffer
    }                                                               //
    while (k < 0 || k >= t_keys) {                                  // Ciclo para preguntar por la clave
        printf ("Clave? :  ");                                      // Pregunta por la clave
        scanf ("%s", key);                                          // Guardamos la clave
        if (strstr (key, "1-2")) k = 0;                             // Realizamos el mismo procedimiento
        else if (strstr (key, "3-4")) k = 1;                        // que hicimos para guardar los dias
        else if (strstr (key, "5-6")) k = 2;                        // En caso de que por
        else if (strstr (key, "7-8")) k = 3;                        // A, B, C o motivo
        else if (strstr (key, "9-10")) k = 4;                       // Se decidan implementar mas claves,
        else if (strstr (key, "11-12")) k = 5;                      // Deben ser añadidas
        else if (strstr (key, "13-14")) k = 6;                      // Aqui, ademas t_keys debe ser modificado
        else                                                        // Si no se encuentra concordancias,
        printf ("%s < no se reconoce como clave valida\n", key);    // Señala que la clave ingresada no es valida
        clearstdin ();                                              // Limpiamos el buffer
    }
    keys = tt [d];                                                  // Montamos las claves del dia que elegimos
    return keys [k];                                                // Retornamos la lista de la clave que escojimos
}
void SeeClass (Class* c){                                           // Procedimiento para ver la
    if (!c) return;                                                 // informacion en detalle
    printf ("Asignatura :  %s\n", c -> name);                       // sobre una clase
    printf ("Ubicacion  :  %s\n", c -> location);                   // especifica
}
void _seekey (List* list){                                          // Procedimiento complementario para SeeKey o derivados (Solo imprime una lista)
    clearscr ();                                                    // Limpiamos la consola para mayor comodidad
    Class *c = first (list);                                        // Variable para rescatar un curso o actividad
    printf ("CONTENIDO ACTUAL:\n\n");                               // Procedemos a mostrar el contenido
    if (!c){                                                        // Si NO hay un elemento dentro de esta lista
        printf ("*Nada que mostrar\n");                             // Imprimimos que no hay nada que mostrar
        return;                                                     // Retornamos a donde estabamos
    }                                                               // En caso de que si encuentre algo
    while (c){                                                      // Verificaremos que elemento es mediante la variable c -> type
        if (c -> type == 0) SeeClass (c);                           // y procedemos a imprimir
        c = next (list);                                            // cada item de la lista segun corresponda
        printf ("\n");                                              // Imprimimos un pequeño separador
        if (c) printf ("------------------------\n\n");             // Para separar actividades
    }
}
void AddClass (void** tt){                                          // Procedimiento para añadir una actividad a una clave
    List* list = MountKey (tt);                                     // Montamos la lista con las actividades de la clave
    _seekey (list);                                                 // Mostramos por pantalla la lista de actividades de la clave respectiva
    pushFront (list,createClass());                                 // llamamos a createClass e insertamos la clase creada, las clases siempre son 'Front'
}
void SeeKey (void** tt){                                            // Procedimiento para ver una clave en detalle
    List* list = MountKey (tt);                                     // Montamos la lista con las actividades de la clave
    _seekey (list);                                                 // Invocamos a _seekey para ver que tenemos en la lista
}
void Remove (void** tt){                                            // Procedimiento para eliminar una actividad a una clave
    List* list = MountKey (tt);                                     // Montamos la lista con las actividades de la clave
    _seekey (list);                                                 // Mostramos por pantalla la lista de actividades de esa clave
    char* Name = NULL;                                              // Variable para el nombre del elemento a eliminar
    Class* c = first (list);                                        // Rescatamos el primer elemento de la lista
    if (!c) return;                                                 // Si está vacía volvemos a donde estabamos
    printf ("\nNombre del elemento a eliminar? : ");                // Solicitamos el nombre a del elemento a elimnar
    Name = readString ();                                           // Guardamos el nombre
    while (c){                                                      // Ciclo diseñado
        if (strstr (str_tolower(c -> name), str_tolower(Name))){    // Para buscar el nombre dentro de la lista
            printf ("Se eliminara %s, ", c -> name);                // Si lo encuentra solicita
            if (confirm ("aceptar?")){                              // Confirmar que realmente se desea eliminar dicho elemento
                popCurrent (list);                                  // de la lista
                break;                                              // En caso contrario
            }                                                       // Seguimos buscando
        }                                                           // concordancias con 'Nombre'
        c = next (list);                                            // Hasta el final de la lista
    }
}
