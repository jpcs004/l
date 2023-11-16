#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

//função de comparação
int compareStrings(const void *a, const void *b);

//função que conta as palavras no arquivo
int countWords(FILE *file);

int main() {
    FILE *file;
    char word[MAX_WORD_LENGTH];
    char **word_array = NULL;
    int word_count = 0;

    // Abre o arquivo
    file = fopen("lusiadas.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    // Conta o número total de palavras no arquivo
    word_count = countWords(file);

    // Alocar o array com o número exato de palavras
    word_array = (char **)malloc(word_count * sizeof(char *));
    if (word_array == NULL) {
        printf("Erro ao alocar memória");
        fclose(file);
        return 1;
    }

    // Lê as palavras do arquivo
    for (int i = 0; i < word_count; i++) {
        if (fscanf(file, "%s", word) == 1) {
            // Converte a palavra para minúsculas
            for (int j = 0; word[j]; j++) {
                word[j] = tolower(word[j]);
            }

            // Aloca memória para a palavra
            word_array[i] = (char *)malloc(strlen(word) + 1);
            if (word_array[i] == NULL) {
                printf("Erro ao alocar memória");
                fclose(file);
                return 1;
            }

            // Copia a palavra para a memória alocada
            strcpy(word_array[i], word);
        }
    }

    // Fecha o arquivo
    fclose(file);

    // Ordena o array de palavras
    qsort(word_array, word_count, sizeof(char *), compareStrings);

    // Imprime as palavras em ordem alfabética
    for (char c = 'a'; c <= 'z'; c++) {
        printf("Palavras começando com '%c':\n", c);
        for (int i = 0; i < word_count; i++) {
            if (word_array[i][0] == c) {
                printf("%s\n", word_array[i]);
            }
        }
        printf("\n");
    }

    // Imprime o número total de palavras
    printf("Número total de palavras: %d\n", word_count);

    // Libera a memória alocada
    for (int i = 0; i < word_count; i++) {
        free(word_array[i]);
    }
    free(word_array);

    return 0;
}





// Função que conta as palavras no arquivo
int countWords(FILE *file) {
    int word_count = 0;
    char word[MAX_WORD_LENGTH];

    while (fscanf(file, "%s", word) == 1) {
        word_count++;
    }

    // Retorna ao início do arquivo para a segunda passagem
    fseek(file, 0, SEEK_SET);

    return word_count;
}


// Função de comparação para qsort
int compareStrings(const void *a, const void *b) {
    return ( *(int*)a - *(int*)b );
}
