#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include "mauri.h"


// Ajusta las definicones para limpiar la consola del sistema
#ifdef _WIN32                       // En caso de que se ejecute bajo Windows
#define clear "cls"                 // Se define como clear cls
#else                               // En caso de que se ejecute bajo UNIX
#define clear "clear"               // Se define como clear clear
#endif
void clearscr () {system (clear);}  // Segun corresponda ser� system ("cls") o systenm ("clear")

// Procedimiento para pasar un string completo a minusculas
char* str_tolower (char *string) {
    char* ret = malloc (sizeof (char) * strlen (string));
    int i = 0;
    while (string [i] != '\0') {
        if(string [i] >= 'A' && string [i] <= 'Z')
            ret [i] = string [i] + (char) 32;
        else
            ret [i] = string [i];
        i ++;
    }
    ret [i] = '\0';
    return strdup (ret);
}
// Procedimiento para pasar un string completo a mayusculas
char* str_toupper (char *string) {
    char* ret = malloc (sizeof (char) * strlen (string));
    int i = 0;
    while (string [i] != '\0') {
        if(string [i] >= 'a' && string [i] <= 'z')
            ret [i] = string [i] - (char) 32;
        else
            ret [i] = string [i];
        i ++;
    }
    ret [i] = '\0';
    return strdup (ret);
}



// Simula una pausa en la ejeccui�n del programa
void pause ()
{
    getchar ();
    printf ("\nPresione <ENTER> para continuar ");
    while (getchar() != '\n');
}

// readString supone almacenar todo el contenido ingresado por teclado hasta el salto de linea
char* readString ()
{
    char* buffer = NULL;                    // String auxiliar
    int capacity = 0;                       // Capacidad del string
    int size = 0;                           // Tama�o actual del string
    int c;                                  // Variable para el caracter
    char* temp = NULL;                      // String temporal
    char* str = NULL;                       // String final
    while ((c = fgetc (stdin)) != '\n')                             // Si falla agregar 'c != EOF'
    {
        if (size + 1 > capacity)                                    // Aumenta la capacidad del buffer
        {
            if (capacity == 0) capacity = 32;                       // Determina la nueva capacidad, por defecto 32
            else if (capacity <= (UINT_MAX / 2)) capacity *= 2;     // Duplica la capacidad
            else
            {
                free (buffer);                                      // Libera el buffer
                return NULL;                                        // Retorna NULL
            }
            temp = realloc (buffer, capacity * sizeof(char));       // Reajusta la capacidad
            if (!temp)                                              // Se corrobora que exista contenido en el 'string'
            {
                free (buffer);                                      // Libera el buffer
                return NULL;                                        // Retorna NULL
            }
            buffer = temp;                                          // Mueve a buffer el contenido del string temporal
        }
        buffer [size ++] = c;                       // Copia el caracter al buffer
    }
    if (size == 0 && c == EOF) return NULL;         // Devuelve NULL si el usuario no ingresa contenido alguno
    str = malloc ((size + 1) * sizeof(char));       // Minimiza el buffer
    strncpy (str, buffer, size);                    // Copia el string del buffer al string final
    free (buffer);                                  // Libera el buffer
    str [size] = '\0';                              // A�ade el '\0' y retorna
    return strdup (str);                            // Retorna
}

// Confirm supone validar un 'Si' o 'No' (Retorna 1 en caso de ser afirmativo o 0 en caso de resivir cualquier otro valor)
int confirm (char* text)                    // Recive la pregunta a validar
{
    char c;                                 // Variable para la respuesta
    printf ("%s (Y/N): ", text);            // Imprime el texto
    c = getchar ();                         // Guarda la respuesta
    if (c == 'Y' || c == 'y') return 1;     // Retorna si o no
    else return 0;
}

// QError muestra un error por pantalla y termina la ejeccución del programa
void QError (char *display_error)
{
    printf ("\nERROR!: > %s\n", display_error);
    exit (EXIT_FAILURE);
}

// Numb To Day recive un numero e imprime en pantalla el nombre del dia correspondiente
#define _1DAY "LUNES"
#define _2DAY "MARTES"
#define _3DAY "MIERCOLES"
#define _4DAY "JUEVES"
#define _5DAY "VIERNES"
#define _6DAY "SABADO"
#define _7DAY "DOMINGO"
void NumbToDay (int number)
{
    if (!(number >= 1 && number <= 7)) return;
    if (number == 1) printf (_1DAY);
    if (number == 2) printf (_2DAY);
    if (number == 3) printf (_3DAY);
    if (number == 4) printf (_4DAY);
    if (number == 5) printf (_5DAY);
    if (number == 6) printf (_6DAY);
    if (number == 7) printf (_7DAY);
}
