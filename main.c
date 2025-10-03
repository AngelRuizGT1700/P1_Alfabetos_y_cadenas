#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LONGITUD 50
#define MAX_CADENAS 10
#define MAX_SUBSECUENCIAS 10000

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
void calcularLongitud();
void potenciaPositiva();
void potenciaNegativa();
void generarPrefijos();
void generarSufijos();
void generarSubcadenas();
void generarSubsecuencias();
void concatenacion();
void guardarResultadoEnArchivo(char *operacion, char *resultado);
void generarSubsecuenciasRecursivo(char *cadena, int indice, char *actual, int len_actual, char **resultados, int *contador);

int main()
{
    printf("PRACTICA 1 - ALFABETOS Y CADENAS \n\n");
    menuCadenas();
    return 0;
}

void menuCadenas()
{
    int opcion;

    do
    {
        printf("\n=== MENU PRINCIPAL ===\n");
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
        printf("\n=== OPERACIONES CON CADENAS ===\n");
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
        printf("\n=== OPERACIONES CON UNA CADENA ===\n");
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
        getchar();

        switch (opcion)
        {
        case 1:
            calcularLongitud();
            break;
        case 2:
            potenciaPositiva();
            break;
        case 3:
            potenciaNegativa();
            break;
        case 4:
            generarPrefijos();
            break;
        case 5:
            generarSufijos();
            break;
        case 6:
            generarSubcadenas();
            break;
        case 7:
            generarSubsecuencias();
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
        printf("\n=== OPERACIONES CON DOS CADENAS ===\n");
        printf("1. Concatenación\n");
        printf("2. Volver atrás\n");
        printf("Opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            concatenacion();
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
    printf("Ingrese la cadena (máx %d caracteres alfanuméricos): ", MAX_LONGITUD);
    fgets(entrada, sizeof(entrada), stdin);

    entrada[strcspn(entrada, "\n")] = 0;
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

void calcularLongitud()
{
    int indice;

    if (total_cadenas == 0)
    {
        printf("No hay cadenas disponibles.\n");
        return;
    }

    verCadenas();
    printf("Seleccione el número de la cadena: ");
    scanf("%d", &indice);
    getchar();

    if (indice < 1 || indice > total_cadenas)
    {
        printf("Índice no válido.\n");
        return;
    }

    Cadena *cadena = coleccion[indice - 1];
    printf("Longitud de '%s': %d\n", cadena->contenido, cadena->longitud);

    char resultado[100];
    sprintf(resultado, "Longitud: %d", cadena->longitud);
    guardarResultadoEnArchivo("Longitud", resultado);
}

void potenciaPositiva()
{
    if (total_cadenas == 0)
    {
        printf("No hay cadenas disponibles.\n");
        return;
    }

    verCadenas();
    int indice, exponente;
    printf("Seleccione el número de la cadena: ");
    scanf("%d", &indice);
    printf("Ingrese el exponente positivo: ");
    scanf("%d", &exponente);
    getchar();

    if (indice < 1 || indice > total_cadenas)
    {
        printf("Índice no válido.\n");
        return;
    }

    if (exponente < 0)
    {
        printf("Error: Esta función es para potencia positiva.\n");
        return;
    }

    Cadena *cadena = coleccion[indice - 1];
    char resultado[MAX_LONGITUD * exponente + 1];
    resultado[0] = '\0';

    for (int i = 0; i < exponente; i++)
    {
        strcat(resultado, cadena->contenido);
    }

    if (total_cadenas < MAX_CADENAS && strlen(resultado) <= MAX_LONGITUD)
    {
        coleccion[total_cadenas] = crearCadena(resultado);
        printf("Resultado: '%s' (guardado como cadena #%d)\n", resultado, total_cadenas + 1);
        total_cadenas++;
    }
    else
    {
        printf("Resultado: '%s'\n", resultado);
        if (strlen(resultado) > MAX_LONGITUD)
        {
            printf("No se pudo guardar: excede el límite de %d caracteres.\n", MAX_LONGITUD);
        }
    }

    guardarResultadoEnArchivo("Potencia Positiva", resultado);
}

void potenciaNegativa()
{
    if (total_cadenas == 0)
    {
        printf("No hay cadenas disponibles.\n");
        return;
    }

    verCadenas();
    int indice, exponente;
    printf("Seleccione el número de la cadena: ");
    if (scanf("%d", &indice) != 1)
    {
        printf("Entrada inválida.\n");
        return;
    }
    printf("Ingrese el exponente negativo: ");
    if (scanf("%d", &exponente) != 1)
    {
        printf("Entrada inválida.\n");
        return;
    }
    getchar();

    if (indice < 1 || indice > total_cadenas)
    {
        printf("Índice no válido.\n");
        return;
    }

    if (exponente >= 0)
    {
        printf("Error: Esta función es para potencia negativa.\n");
        return;
    }

    Cadena *cadena = coleccion[indice - 1];
    int len = cadena->longitud;

    exponente = -exponente;

    char invertida[len + 1];
    for (int i = 0; i < len; i++)
        invertida[i] = cadena->contenido[len - 1 - i];
    invertida[len] = '\0';

    int total_len = len * exponente;
    char *resultado = malloc(total_len + 1);
    if (!resultado)
    {
        printf("Error de memoria.\n");
        return;
    }

    resultado[0] = '\0';
    for (int i = 0; i < exponente; i++)
        strcat(resultado, invertida);

    printf("Resultado: '%s'\n", resultado);

    if (total_cadenas < MAX_CADENAS)
    {
        coleccion[total_cadenas] = crearCadena(resultado);
        printf("Resultado guardado como cadena #%d\n", total_cadenas + 1);
        total_cadenas++;
    }

    guardarResultadoEnArchivo("Potencia Negativa", resultado);

    free(resultado);
}

void generarPrefijos()
{
    if (total_cadenas == 0)
    {
        printf("No hay cadenas disponibles.\n");
        return;
    }

    verCadenas();
    int indice;
    printf("Seleccione el número de la cadena: ");
    scanf("%d", &indice);
    getchar();

    if (indice < 1 || indice > total_cadenas)
    {
        printf("Índice no válido.\n");
        return;
    }

    Cadena *cadena = coleccion[indice - 1];
    printf("\n=== PREFIJOS DE '%s' ===\n", cadena->contenido);

    FILE *archivo = fopen("prefijos.txt", "w");
    fprintf(archivo, "Prefijos de '%s':\n", cadena->contenido);

    for (int i = 0; i <= cadena->longitud; i++)
    {
        char prefijo[MAX_LONGITUD + 1];
        strncpy(prefijo, cadena->contenido, i);
        prefijo[i] = '\0';
        printf("%d. '%s'\n", i + 1, prefijo);
        fprintf(archivo, "%d. '%s'\n", i + 1, prefijo);
    }

    fclose(archivo);
    printf("Los prefijos se han guardado en 'prefijos.txt'\n");
}

void generarSufijos()
{
    if (total_cadenas == 0)
    {
        printf("No hay cadenas disponibles.\n");
        return;
    }

    verCadenas();
    int indice;
    printf("Seleccione el número de la cadena: ");
    scanf("%d", &indice);
    getchar();

    if (indice < 1 || indice > total_cadenas)
    {
        printf("Índice no válido.\n");
        return;
    }

    Cadena *cadena = coleccion[indice - 1];
    printf("\n=== SUFIJOS DE '%s' ===\n", cadena->contenido);

    FILE *archivo = fopen("sufijos.txt", "w");
    fprintf(archivo, "Sufijos de '%s':\n", cadena->contenido);

    for (int i = 0; i <= cadena->longitud; i++)
    {
        char sufijo[MAX_LONGITUD + 1];
        strcpy(sufijo, cadena->contenido + i);
        printf("%d. '%s'\n", i + 1, sufijo);
        fprintf(archivo, "%d. '%s'\n", i + 1, sufijo);
    }

    fclose(archivo);
    printf("Los sufijos se han guardado en 'sufijos.txt'\n");
}

void generarSubcadenas()
{
    if (total_cadenas == 0)
    {
        printf("No hay cadenas disponibles.\n");
        return;
    }

    verCadenas();
    int indice;
    printf("Seleccione el número de la cadena: ");
    scanf("%d", &indice);
    getchar();

    if (indice < 1 || indice > total_cadenas)
    {
        printf("Índice no válido.\n");
        return;
    }

    Cadena *cadena = coleccion[indice - 1];
    printf("\n=== SUBCADENAS DE '%s' ===\n", cadena->contenido);

    FILE *archivo = fopen("subcadenas.txt", "w");
    fprintf(archivo, "Subcadenas de '%s':\n", cadena->contenido);

    int contador = 1;
    for (int len = 1; len <= cadena->longitud; len++)
    {
        for (int inicio = 0; inicio <= cadena->longitud - len; inicio++)
        {
            char subcadena[MAX_LONGITUD + 1];
            strncpy(subcadena, cadena->contenido + inicio, len);
            subcadena[len] = '\0';
            printf("%d. '%s'\n", contador, subcadena);
            fprintf(archivo, "%d. '%s'\n", contador, subcadena);
            contador++;
        }
    }

    // Cadena vacía
    printf("%d. '%s'\n", contador, "");
    fprintf(archivo, "%d. '%s'\n", contador, "");

    fclose(archivo);
    printf("Las subcadenas se han guardado en 'subcadenas.txt'\n");
}

void generarSubsecuenciasRecursivo(char *cadena, int indice, char *actual, int len_actual, char **resultados, int *contador)
{
    if (indice == strlen(cadena))
    {
        actual[len_actual] = '\0';
        // Verificar si ya existe esta subsecuencia
        for (int i = 0; i < *contador; i++)
        {
            if (strcmp(resultados[i], actual) == 0)
            {
                return;
            }
        }
        strcpy(resultados[*contador], actual);
        (*contador)++;
        return;
    }

    // Incluir el carácter actual
    actual[len_actual] = cadena[indice];
    generarSubsecuenciasRecursivo(cadena, indice + 1, actual, len_actual + 1, resultados, contador);

    // Excluir el carácter actual
    generarSubsecuenciasRecursivo(cadena, indice + 1, actual, len_actual, resultados, contador);
}

void generarSubsecuencias()
{
    if (total_cadenas == 0)
    {
        printf("No hay cadenas disponibles.\n");
        return;
    }

    verCadenas();
    int indice;
    printf("Seleccione el número de la cadena: ");
    scanf("%d", &indice);
    getchar();

    if (indice < 1 || indice > total_cadenas)
    {
        printf("Índice no válido.\n");
        return;
    }

    Cadena *cadena = coleccion[indice - 1];

    // Verificar longitud máxima para subsecuencias
    if (cadena->longitud > 14)
    {
        printf("Advertencia: La cadena tiene longitud %d (>14). El cálculo puede ser lento.\n", cadena->longitud);
        printf("¿Desea continuar? (s/n): ");
        char respuesta = getchar();
        if (respuesta != 's' && respuesta != 'S')
        {
            return;
        }
    }

    printf("\n=== SUBSECUENCIAS DE '%s' ===\n", cadena->contenido);

    // Reservar memoria para las subsecuencias
    char **subsecuencias = malloc(MAX_SUBSECUENCIAS * sizeof(char *));
    for (int i = 0; i < MAX_SUBSECUENCIAS; i++)
    {
        subsecuencias[i] = malloc(MAX_LONGITUD + 1);
    }

    char actual[MAX_LONGITUD + 1];
    int contador = 0;

    generarSubsecuenciasRecursivo(cadena->contenido, 0, actual, 0, subsecuencias, &contador);

    FILE *archivo = fopen("subsecuencias.txt", "w");
    fprintf(archivo, "Subsecuencias de '%s':\n", cadena->contenido);

    for (int i = 0; i < contador; i++)
    {
        printf("%d. '%s'\n", i + 1, subsecuencias[i]);
        fprintf(archivo, "%d. '%s'\n", i + 1, subsecuencias[i]);
    }

    fclose(archivo);
    printf("Total de subsecuencias: %d\n", contador);
    printf("Las subsecuencias se han guardado en 'subsecuencias.txt'\n");

    // Liberar memoria
    for (int i = 0; i < MAX_SUBSECUENCIAS; i++)
    {
        free(subsecuencias[i]);
    }
    free(subsecuencias);
}

// OPERACIONES CON DOS CADENAS

void concatenacion()
{
    if (total_cadenas < 2)
    {
        printf("Se necesitan al menos 2 cadenas para esta operación.\n");
        return;
    }

    verCadenas();
    int indice1, indice2;
    printf("Seleccione el número de la primera cadena: ");
    scanf("%d", &indice1);
    printf("Seleccione el número de la segunda cadena: ");
    scanf("%d", &indice2);
    getchar();

    if (indice1 < 1 || indice1 > total_cadenas || indice2 < 1 || indice2 > total_cadenas)
    {
        printf("Índice no válido.\n");
        return;
    }

    Cadena *cadena1 = coleccion[indice1 - 1];
    Cadena *cadena2 = coleccion[indice2 - 1];

    char resultado[MAX_LONGITUD * 2 + 1];
    strcpy(resultado, cadena1->contenido);
    strcat(resultado, cadena2->contenido);

    // Verificar si podemos guardar la nueva cadena
    if (total_cadenas < MAX_CADENAS && strlen(resultado) <= MAX_LONGITUD)
    {
        coleccion[total_cadenas] = crearCadena(resultado);
        printf("Resultado: '%s' (guardado como cadena #%d)\n", resultado, total_cadenas + 1);
        total_cadenas++;
    }
    else
    {
        printf("Resultado: '%s'\n", resultado);
        if (strlen(resultado) > MAX_LONGITUD)
        {
            printf("No se pudo guardar: excede el límite de %d caracteres.\n", MAX_LONGITUD);
        }
    }

    guardarResultadoEnArchivo("Concatenación", resultado);
}

// FUNCIONES AUXILIARES

void guardarResultadoEnArchivo(char *operacion, char *resultado)
{
    FILE *archivo = fopen("operaciones.txt", "a");
    if (archivo == NULL)
    {
        archivo = fopen("operaciones.txt", "w");
    }

    fprintf(archivo, "Operación: %s\n", operacion);
    fprintf(archivo, "Resultado: %s\n\n", resultado);
    fclose(archivo);
}