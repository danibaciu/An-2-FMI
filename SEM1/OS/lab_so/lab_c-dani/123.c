#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
//ex 2
int count_occurrences(const char * text, const char * word)
{
    int i, j, count = 0, stringLen = strlen(text), searchLen = strlen(word);
    bool found;
    for (i = 0; i <= stringLen - searchLen; i++) {
        found = true;
        for(j = 0; j < searchLen; j++) {
            if(text[i + j] != word[j]) {
                found = false;
                break;
            }
        }
        if(found)
            count++;
    }
    return count;
}

//ex 3
char* replaceWord(const char* s, const char* s1, const char* s2)
{
    char* result;
    int i = 0, cnt = 0, len2 = strlen(s2), len1 = strlen(s1);

    cnt = count_occurrences(s,s1);

    result = (char*)malloc(i + cnt * (len2 - len1) + 1);

    while (*s) {
        if (strstr(s, s1) == s) {
            strcpy(&result[i], s2);
            i += len2;
            s += len1;
        }
        else
            result[i++] = *s++;
    }
    result[i] = '\0';
    return result;
}


//ex1
int main()
{
    int **mat;
    int i, j, n;

    printf("nr. linii si coloane = ");
    scanf("%d", &n);

    mat = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        mat[i] = calloc(n, sizeof(int));

    for (i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);

    printf("Matricea este:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%2d", mat[i][j]);
        printf("\n");
    }


    if (n % 2)
        printf("Elementul de la intersectia diagonalelor:%d\n", mat[n / 2][n / 2]);

    printf("Elementele de pe diagonala principala sunt: ");
    for(i = 0; i < n; i++)
        printf("%d ", mat[i][i]);
    printf("\nElementele de pe diagonala secundara sunt: ");
    for(i = 0; i < n; i++)
        printf("%d ", mat[i][n - i - 1]);

    //eliberarea memoriei
    for (i = 0; i < n; i++)
        free(mat[i]);
    free(mat);

    return 0;
}
