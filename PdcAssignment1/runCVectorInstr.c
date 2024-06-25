#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <immintrin.h>


void matrix_multiply_avx2(int **matrix1, int **matrix2, int **result, int rows1, int cols1, int cols2)
{
    for (int i = 0; i < rows1; ++i)
    {
        for (int j = 0; j < cols2; ++j)
        {
            __m256i sum = _mm256_setzero_si256();

            for (int k = 0; k < cols1; k++)
            {
                __m256i vec1 = _mm256_loadu_si256((__m256i *)&matrix1[i][k]);
                __m256i vec2 = _mm256_loadu_si256((__m256i *)&matrix2[k][j]);

                __m256i prod = _mm256_mullo_epi32(vec1, vec2);

                sum = _mm256_add_epi32(sum, prod);
            }

            _mm256_storeu_si256((__m256i *)&result[i][j], sum);
        }
    }
}




void free_matrix(int **matrix, int rows)
{
    for (int i = 0; i < rows; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void call_read_and_calc(const char *file_path)
{
    FILE *fp = fopen(file_path, "r");

    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    char dimension[256];

    for (int i = 0; i < 2; i++)
    {
        if (fgets(dimension, sizeof(dimension), fp) == NULL)
        {
            perror("Error reading file");
            fclose(fp);
            return;
        }
    }

    if (fgets(dimension, sizeof(dimension), fp) == NULL)
    {
        perror("Error reading file");
        fclose(fp);
        return;
    }

    printf("Dim is: %s\n", dimension);
    int rows = atoi(strtok(dimension, "X"));
    int cols = atoi(strtok(NULL, "X"));

    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL)
        {
            perror("Memory allocation failed");
            free_matrix(matrix, i);
            fclose(fp);
            return;
        }
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (fscanf(fp, "%d", &matrix[i][j]) != 1)
            {
                perror("Error reading matrix element");
                free_matrix(matrix, rows);
                fclose(fp);
                return;
            }

            // Check for the end of line or file
            int nextChar = fgetc(fp);
            if (nextChar == '\n' || nextChar == EOF)
            {
                break;
            }
        }
    }

    if (fgets(dimension, sizeof(dimension), fp) == NULL)
    {
        printf("File End \n");
    }
    printf("Dim is: %s\n", dimension);
    int rows2 = atoi(strtok(dimension, "X"));
    int cols2 = atoi(strtok(NULL, "X"));
    int **matrix2 = (int **)malloc(rows2 * sizeof(int *));
    for (int i = 0; i < rows2; ++i)
    {
        matrix2[i] = (int *)malloc(cols2 * sizeof(int));
        if (matrix2[i] == NULL)
        {
            perror("Memory allocation failed");
            free_matrix(matrix, rows);
            fclose(fp);
            return;
        }
    }

    for (int i = 0; i < rows2; ++i)
    {
        for (int j = 0; j < cols2; ++j)
        {
            if (fscanf(fp, "%d", &matrix2[i][j]) != 1)
            {
                perror("Error reading matrix element");
                free_matrix(matrix, rows);
                free_matrix(matrix2, rows2);
                fclose(fp);
                return;
            }

            int nextChar = fgetc(fp);
            if (nextChar == '\n' || nextChar == EOF)
            {
                break;
            }
        }
    }

    fclose(fp);

    // Print the matrices
    printf("Matrix:\n");
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }



    printf("Matrix2:\n");
    for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < cols2; ++j) {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }

    int **result = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        result[i] = (int *)malloc(cols2* sizeof(int));
        if (result[i] == NULL) {
            perror("Memory allocation failed");
            free_matrix(matrix, rows);
            free_matrix(matrix2, rows);
            fclose(fp);
            return;
        }
    }

    if(cols==rows2)
    {
    matrix_multiply_avx2(matrix, matrix2, result, rows, cols,cols2);
    }
    else{
        printf("MATRIX MULTIPLICATION NOT POSSIBLE \n");
    }
    // Print the result matrix
    printf("Result:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols2; ++j) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    // free_matrix(matrix, rows);
    // free_matrix(matrix2, rows2);
    // free_matrix(result, rows);
}

int main() {
    call_read_and_calc("/home/hamad/Desktop/PdcAssignment1/inputFIle.txt");
    return 0;
}
