#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100

FILE *AbreFicheiro(char *nome, char *mode)
{
    FILE *fp;
    fp = fopen(nome, mode);
    if (fp == NULL)
    {
        exit(0);
    }
    return (fp);
}
int sortstring(const void *str1, const void *str2)
{
    return strcmp(*(const char **)str1, *(const char **)str2);
}

int count_words(char **word_array, int n_total_words, char letter)
{
    int i = 0, n_palavras_por_letras = 0;

    for (i = 0; i < n_total_words; i++)
    {
        if (word_array[i][0] == letter || word_array[i][0] == letter - 'a' + 'A')
        {
            n_palavras_por_letras++;
        }
    }

    return n_palavras_por_letras;
}

int *count_words_2(char **word_array, int n_total_words)
{
    char ch = '\0';
    int i, n_palavras_por_letras = 0;
    int *count_letters = (int *)calloc(26, sizeof(int));

    for (ch = 'a'; ch <= 'z'; ch++)
    {
        for (i = 0; i < n_total_words; i++)
        {
            if (word_array[i][0] == ch || word_array[i][0] == ch - 'a' + 'A')
            {
                count_letters[ch - 'a']++;
            }
        }
    }
    return count_letters;
}

int main(int argc, char *argv[])
{
    /*VARIÁVEIS*/
    int counter = 0, i = 0;
    int *count_letters = NULL;
    FILE *fp = NULL;
    char palavra[MAX_STR], ch = '\0';
    char *ficheiro = "Lab 1 - lusiadas-words.txt";
    char **word_array = NULL;

    fp = AbreFicheiro(ficheiro, "r");

    while (fscanf(fp, "%s", palavra) == 1)
    {

        counter++;
    }

    fseek(fp, 0, SEEK_SET);

    word_array = (char **)malloc(counter * (sizeof(char *)));

    for (i = 0; i < counter; i++)
    {

        if (fscanf(fp, "%s", palavra) == 1)
        {
            word_array[i] = (char *)malloc(MAX_STR * sizeof(char));
            strcpy(word_array[i], palavra);
        }
    }

    qsort(word_array, counter, sizeof(char *), sortstring);

    fclose(fp);

    fprintf(stdout, "\nNumero total de strings: %d\n", counter);

    for (ch = 'a'; ch <= 'z'; ch++)
    {
        printf("%c: %d\n", ch, count_words(word_array, counter, ch));
    }

    for (ch = 'a'; ch <= 'z'; ch++)
    {
        count_letters = count_words_2(word_array, counter);
    }

    for (i = 0; i <= 25; i++){
        fprintf(stdout, "%d ", count_letters[i]);
    }
        free(count_letters);

        for (i = 0; i < counter; i++)
        {
            free(word_array[i]);
        }
        free(word_array);

        return 0;
    }
