#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LONGITUD 50
#define MAX_CADENAS 10

typedef struct
{
    char contenido[MAX_LONGITUD + 1];
    int longitud;
} Cadena;

Cadena *coleccion[MAX_CADENAS];
int total_cadenas = 0;

void menuCadenas();
Cadena *crearCadena(char *cadena);
void anadirCadena();
void verCadenas();
void menuOperaciones();
void menuOperacionesUnaCadena();
void menuOperacionesDosCadenas();

int main()
{
    menuCadenas();

    return 0;
}

void menuCadenas()
{
    int opcion;

    do
    {
        printf("Seleccione una opción:\n");
        printf("1. Añadir cadena\n");
        printf("2. Ver cadenas guardadas\n");
        printf("3. Operar con cadenas\n");
        printf("4. Salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            anadirCadena();
            break;
        case 2:
            verCadenas();
            break;
        case 3:
            menuOperaciones();
            break;
        case 4:
            printf("Vuelva pronto... :)\n");
            break;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
            break;
        }
    } while (opcion != 4);
}

void menuOperaciones()
{
    int opcion;

    do
    {
        printf("Seleccione una opción:\n");
        printf("1. Operaciones con una cadena\n");
        printf("2. Operaciones con dos cadenas\n");
        printf("3. Volver atrás\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            menuOperacionesUnaCadena();
            break;
        case 2:
            menuOperacionesDosCadenas();
            break;
        case 3:
            printf("Volviendo atrás...\n");
            break;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
            break;
        }
    } while (opcion != 3);
}

void menuOperacionesUnaCadena()
{
    int opcion;

    do
    {
        printf("\nSeleccione una operación:\n");
        printf("1. Longitud de una cadena\n");
        printf("2. Potencia Positiva\n");
        printf("3. Potencia Negativa\n");
        printf("4. Generación de Prefijos\n");
        printf("5. Generación de Sufijos\n");
        printf("6. Generación de Subcadenas\n");
        printf("7. Generación de Subsecuencias\n");
        printf("8. Volver atrás\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            printf("Volviendo atrás...\n");
            break;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
            break;
        }
    } while (opcion != 8);
}

void menuOperacionesDosCadenas()
{
    int opcion;

    do
    {
        printf("\nSeleccione una operación:\n");
        printf("1. Concatenación\n");
        printf("2. Volver atrás\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            break;
        case 2:
            printf("Volviendo atrás...\n");
            break;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
            break;
        }
    } while (opcion != 2);
}

Cadena *crearCadena(char *cadena)
{
    Cadena *nueva = malloc(sizeof(Cadena));
    strncpy(nueva->contenido, cadena, MAX_LONGITUD);
    nueva->contenido[MAX_LONGITUD] = '\0';
    nueva->longitud = strlen(nueva->contenido);
    return nueva;
}

void anadirCadena()
{
    if (total_cadenas >= MAX_CADENAS)
    {
        printf("Error: La colección está llena.\n");
        return;
    }

    char entrada[100];
    printf("Ingrese la cadena (máx %d caracteres): ", MAX_LONGITUD);
    fgets(entrada, sizeof(entrada), stdin);

    entrada[strcspn(entrada, "\n")] = 0;

    // Validar longitud
    if (strlen(entrada) > MAX_LONGITUD)
    {
        printf("Error: La cadena excede el límite de %d caracteres.\n", MAX_LONGITUD);
        return;
    }

    coleccion[total_cadenas] = crearCadena(entrada);
    total_cadenas++;
    printf("Cadena añadida exitosamente.\n");
}

void verCadenas()
{
    if (total_cadenas == 0)
    {
        printf("No hay cadenas guardadas.\n");
        return;
    }

    printf("\n=== CADENAS GUARDADAS ===\n");
    for (int i = 0; i < total_cadenas; i++)
    {
        printf("%d. '%s' (longitud: %d)\n",
               i + 1,
               coleccion[i]->contenido,
               coleccion[i]->longitud);
    }
    printf("========================\n");
}