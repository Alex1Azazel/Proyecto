#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

// Función para eliminar símbolos no deseados al principio y al final de una palabra
void clean_word(char* word) {
    char* start = word;
    char* end = word + strlen(word) - 1;

    // Eliminar símbolos al principio
    while (start <= end && strchr(".,:;-_!¡¿?()", *start)) {
        start++;
    }

    // Eliminar símbolos al final
    while (end >= start && strchr(".,:;-_!¡¿?", *end)) {
        *end = '\0';
        end--;
    }

    // Mover la palabra limpia al inicio del buffer
    if (start != word) {
        memmove(word, start, end - start + 2);
    }
}

void CargaDiccionario(const char* filename, char words[][MAX_WORD_LENGTH], int frequencies[], int* word_count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char word[MAX_WORD_LENGTH];
    *word_count = 0;

    while (fscanf(file, "%s", word) != EOF) {
        clean_word(word);
        if (strlen(word) == 0) {
            continue;
        }

        int found = 0;
        for (int i = 0; i < *word_count; i++) {
            if (strcmp(words[i], word) == 0) {
                frequencies[i]++;
                found = 1;
                break;
            }
        }
        if (!found && *word_count < MAX_WORDS) {
            strcpy(words[*word_count], word);
            frequencies[*word_count] = 1;
            (*word_count)++;
        }
    }

    fclose(file);

    // Ordenar las palabras alfabéticamente
    for (int i = 0; i < *word_count - 1; i++) {
        for (int j = i + 1; j < *word_count; j++) {
            if (strcmp(words[i], words[j]) > 0) {
                char temp_word[MAX_WORD_LENGTH];
                int temp_freq;

                strcpy(temp_word, words[i]);
                strcpy(words[i], words[j]);
                strcpy(words[j], temp_word);

                temp_freq = frequencies[i];
                frequencies[i] = frequencies[j];
                frequencies[j] = temp_freq;
            }
        }
    }
}

int main() {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int frequencies[MAX_WORDS];
    int word_count;

    // Ruta completa del archivo en el escritorio
    const char* filename = "C:\\Aqui\\Cambia\\La\\Dirección\\De\\Tu\\Archivo"; // Cambia esto según tu sistema operativo y nombre de usuario

    CargaDiccionario(filename, words, frequencies, &word_count);

    for (int i = 0; i < word_count; i++) {
        printf("%s: %d\n", words[i], frequencies[i]);
    }

    return 0;
}