#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "mauri.h"
#include "TimeTable.h"

void NkTab (int nk){                        // Procedimiento para tabular
    if (nk < 8) printf ("      ");          // creará un pequeño intento de compaginado
    if (nk == 8) printf ("     ");          // que conciste en crear un pequeño tabulado al saltarse especios de acuerdo
    if (nk > 8) printf ("    ");            // a la clave que se esté analizando, soporta un maximo de 49 claves diarias
}
Class* createClass (){                      // Procedimiento para crear una clase
    getchar ();                             // Limpia el buffer
    Class *c = malloc (sizeof (Class));     // Reserva espacio
    printf ("\nNombre? : ");                // Pregunta por el
    c -> name = readString ();              // Nombre de la asignatura
    printf ("Donde?  : ");                  // Pregunta por la
    c -> location = readString ();          // Ubicacion
    c -> type = 0;                          // Esto será una clase (type = 0)
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
void PrintTimeTable (void** tt){                        // Procedimiento para imprimir la semana por pantalla
    int d, k, nk;                                       // Variables para recorrer los dias (d) y las claves (k), nk es el numero de la clave (ej: 1-2, 3-4, ..., 13-14)
    void** Keys = NULL;                                 // Variable para almacenar las claves de un dia
    List* list = NULL;                                  // Variable para almacenar la lista de actividades para la clave, si creo que esta demas
    Class *c;                                           // Variable para almacenar un curso (sacado de la lista)
    for (d = 0; d < t_days; d ++){                      // Reocrremos los dias
        printf ("\n");                                  // Saltamos una linea
        NumbToDay(d + 1);                               // Imprimimos el nombre del dia
        printf (":\n");                                 // Hacemos que quede un poco mas bonito
        Keys = tt [d];                                  // Montamos las claves del dia
        nk = 0;                                         // Inicializamos nk en 0
        for (k = 0; k < t_keys; k ++, nk += 2){         // Recorremos las claves del dia
            list = Keys [k];                            // Montamos la lista de actividades de cada clave
            c = first (list);                           // Rescatamos el primer elemento de la lita de actividades
            printf ("Clave: %d-%d", nk+1, nk+2);        // Imprimimos la clave atual
            if (!c) printf ("\n");                      // Si no hay elementos en la lista, se salta una linea
            else NkTab (nk);                            // Si hay elementos llama a NkTab para crear un compaginado
            while (c){                                  // Si existe
                printf (" [%s] ", c -> location);       // Imprimimos su ubicacion
                printf ("%s", c -> name);               // Imprimimos su nombre
                c = next (list);                        // Rescatamos el siguient elemento de la lista y repetimso el proceso
                if (c) printf (",");                    // Si aun quedan elementos por mostrar, imprime una como ','
                else printf ("\n");                     // En caso contrario termina la linea
            }
        }
    }
}
void AddClass (void** tt){                                      // Procedimiento para añadir una actividad a una clave
    int d = -1,k = -1;                                          // Variables para montar el dia y la clave
    char day [10],key[6];                                       // Variables para interactuar con el usuario
    List* list = NULL;                                          // Variable para montar la lista de una clave
    void** keys = NULL;                                         // Variable para montar las claves
    while (d < 0 || d >= t_days) {                              // Ciclo para preguntar por el dia
        printf ("Dia?   :  ");                                  // Preguntamos por el dia
        scanf ("%s", day);                                      // Guardamos el dia
        if (strstr (str_tolower (day), "lunes")) d = 0;         // Vemos que a que dia corresponde
        if (strstr (str_tolower (day), "martes")) d = 1;        // Por defecto son 7
        if (strstr (str_tolower (day), "miercoles")) d = 2;     // Pero solamente validará la respuesta
        if (strstr (str_tolower (day), "jueves")) d = 3;        // cuando el día este dentro del rango de
        if (strstr (str_tolower (day), "viernes")) d = 4;       // dias habiles (t_days)
        if (strstr (str_tolower (day), "sabado")) d = 5;
        if (strstr (str_tolower (day), "domingo")) d = 6;
    }
    while (k < 0 || k >= t_keys) {                              // Ciclo para preguntar por la clave
        printf ("Clave? :  ");                                  // Pregunta por la clave
        scanf ("%s", key);                                      // Guardamos la clave
        if (strstr (key, "1-2")) k = 0;                         // Realizamos el mismo procedimiento
        if (strstr (key, "3-4")) k = 1;                         // que hicimos para guardar los dias
        if (strstr (key, "5-6")) k = 2;
        if (strstr (key, "7-8")) k = 3;
        if (strstr (key, "9-10")) k = 4;
        if (strstr (key, "11-12")) k = 5;
        if (strstr (key, "13-14")) k = 6;
    }
    clearscr ();                                                // Limpiamos la pantalla para mayor comodidad
    printf ("INSERTAR > %s ", str_toupper (day));               // Procedemos a
    printf ("> %s\n", str_toupper (key));                       // indicar la acciona a realizar
    keys = tt [d];                                              // ahora que ya tenemos el dia, montamos dicho dia
    list = keys [k];                                            // ahora de ese dia, montamos la clave
    pushFront (list,createClass());                             // llamamos a createClass e insertamos la clase creada, las clases siempre son 'Front'
}
void SeeClass (Class* c){
    if (!c) return;
    printf ("Asignatura :  %s\n", c -> name);
    printf ("Ubicacion  :  %s\n", c -> location);
}
void SeeKey (void** tt){                                        // Procedimiento para ver una clave en detalle
    int d = -1,k = -1;                                          // Variables para montar el dia y la clave
    char day [10],key[6];                                       // Variables para interactuar con el usuario
    List* list = NULL;                                          // Variable para montar la lista de una clave
    void** keys = NULL;                                         // Variable para montar las claves
    while (d < 0 || d >= t_days) {                              // Ciclo para preguntar por el dia
        printf ("\nDia?   :  ");                                // Preguntamos por el dia
        scanf ("%s", day);                                      // Guardamos el dia
        if (strstr (str_tolower (day), "lunes")) d = 0;         // Vemos que a que dia corresponde
        if (strstr (str_tolower (day), "martes")) d = 1;        // Por defecto son 7
        if (strstr (str_tolower (day), "miercoles")) d = 2;     // Pero solamente validará la respuesta
        if (strstr (str_tolower (day), "jueves")) d = 3;        // cuando el día este dentro del rango de
        if (strstr (str_tolower (day), "viernes")) d = 4;       // dias habiles (t_days)
        if (strstr (str_tolower (day), "sabado")) d = 5;
        if (strstr (str_tolower (day), "domingo")) d = 6;
    }
    while (k < 0 || k >= t_keys) {          // Ciclo para preguntar por la clave
        printf ("Clave? :  ");              // Pregunta por la clave
        scanf ("%s", key);                  // Guardamos la clave
        if (strstr (key, "1-2")) k = 0;     // Realizamos el mismo procedimiento
        if (strstr (key, "3-4")) k = 1;     // que hicimos para guardar los dias
        if (strstr (key, "5-6")) k = 2;
        if (strstr (key, "7-8")) k = 3;
        if (strstr (key, "9-10")) k = 4;
        if (strstr (key, "11-12")) k = 5;
        if (strstr (key, "13-14")) k = 6;
    }
    keys = tt [d];                                      // ahora que ya tenemos el dia, montamos dicho dia
    list = keys [k];                                    // ahora de ese dia, montamos la clave
    Class *c = first (list);                            // Solicitamos el primer elemento de la lista (Que por defecto es una asignatura)
    clearscr ();                                        // Limpiamos la terminal para mayor comodidad
    printf ("VER > %s ", str_toupper (day));            // Procedemos a
    printf ("> %s\n\n", str_toupper (key));             // indicar la acciona a realizar
    if (!c){                                            // Si NO hay un elemento dentro de esta lista
        printf ("*Nada que mostrar\n");                 // Imprimimos que no hay nada que mostrar
        return;                                         // Retornamos a donde estabamos
    }                                                   // En caso de que si encuentre algo
    while (c){                                          // Verificaremos que elemento es mediante la variable c -> type
        if (c -> type == 0) SeeClass (c);               // y procedemos a imprimir
        c = next (list);                                // cada item de la lista segun corresponda
        printf ("\n");                                  // Imprimimos un pequeño separador
        if (c) printf ("------------------------\n\n"); // Para separar actividades
    }
}
