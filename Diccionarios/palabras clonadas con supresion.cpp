#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 1000
#define MAX_WORD_LENGTH 100

void generate_candidates(const char* word, char candidates[MAX_CANDIDATES][MAX_WORD_LENGTH], int* candidate_count);
void add_candidate(char candidates[MAX_CANDIDATES][MAX_WORD_LENGTH], int* candidate_count, const char* new_word);
void sort_candidates(char candidates[MAX_CANDIDATES][MAX_WORD_LENGTH], int candidate_count);

int main() {
    char word[MAX_WORD_LENGTH];
    char candidates[MAX_CANDIDATES][MAX_WORD_LENGTH];
    int candidate_count = 0;

    printf("Introduce la palabra a corregir: ");
    scanf_s("%99s", word, (unsigned)_countof(word));

    generate_candidates(word, candidates, &candidate_count);
    sort_candidates(candidates, candidate_count);

    printf("Palabras candidatas:\n");
    for (int i = 0; i < candidate_count; i++) {
        printf("%s\n", candidates[i]);
    }

    return 0;
}

void generate_candidates(const char* word, char candidates[MAX_CANDIDATES][MAX_WORD_LENGTH], int* candidate_count) {
    int len = strlen(word);

    // Supresión
    for (int i = 0; i < len; i++) {
        char new_word[MAX_WORD_LENGTH];
        strcpy_s(new_word, sizeof(new_word), word);
        memmove(&new_word[i], &new_word[i + 1], len - i);
        add_candidate(candidates, candidate_count, new_word);
    }

    // Sustitución
    for (int i = 0; i < len; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            char new_word[MAX_WORD_LENGTH];
            strcpy_s(new_word, sizeof(new_word), word);
            new_word[i] = c;
            add_candidate(candidates, candidate_count, new_word);
        }
    }

    // Transposición
    for (int i = 0; i < len - 1; i++) {
        char new_word[MAX_WORD_LENGTH];
        strcpy_s(new_word, sizeof(new_word), word);
        char temp = new_word[i];
        new_word[i] = new_word[i + 1];
        new_word[i + 1] = temp;
        add_candidate(candidates, candidate_count, new_word);
    }

    // Inserción
    for (int i = 0; i <= len; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            char new_word[MAX_WORD_LENGTH];
            strcpy_s(new_word, sizeof(new_word), word);
            memmove(&new_word[i + 1], &new_word[i], len - i + 1);
            new_word[i] = c;
            add_candidate(candidates, candidate_count, new_word);
        }
    }
}

void add_candidate(char candidates[MAX_CANDIDATES][MAX_WORD_LENGTH], int* candidate_count, const char* new_word) {
    for (int i = 0; i < *candidate_count; i++) {
        if (strcmp(candidates[i], new_word) == 0) {
            return; // Evitar duplicados
        }
    }
    strcpy_s(candidates[*candidate_count], MAX_WORD_LENGTH, new_word);
    (*candidate_count)++;
}

void sort_candidates(char candidates[MAX_CANDIDATES][MAX_WORD_LENGTH], int candidate_count) {
    for (int i = 0; i < candidate_count - 1; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            if (strcmp(candidates[i], candidates[j]) > 0) {
                char temp[MAX_WORD_LENGTH];
                strcpy_s(temp, sizeof(temp), candidates[i]);
                strcpy_s(candidates[i], sizeof(candidates[i]), candidates[j]);
                strcpy_s(candidates[j], sizeof(candidates[j]), temp);
            }
        }
    }
}