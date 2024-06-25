#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <immintrin.h>
struct my
{
    int **matrix1;
    int **matrix2;
    int **result;
    int matrix_1_row;
    int matrix_1_col;
    int matrix_2_row;
    int matrix_2_col;
    int curr_row;
};

#define cols1 myData->matrix_1_col

void *multiplyIt(void *bigbox)
{
    struct my *myData = (struct my *)bigbox;
    int i = myData->curr_row;

    for (int j = 0; j < myData->matrix_2_col; ++j)
    {
        __m256i sum = _mm256_setzero_si256();

        for (int k = 0; k < cols1; k++)
        {
            __m256i vec1 = _mm256_loadu_si256((__m256i *)&myData->matrix1[i][k]);
            
            __m256i vec2 = _mm256_loadu_si256((__m256i *)&myData->matrix2[k][j]);

            __m256i prod = _mm256_mullo_epi32(vec1, vec2);

            sum = _mm256_add_epi32(sum, prod);
        }

        _mm256_storeu_si256((__m256i *)&myData->result[i][j], sum);
    }

    pthread_exit(NULL);
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
    int col = atoi(strtok(NULL, "X"));

    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = (int *)malloc(col * sizeof(int));
        if (matrix[i] == NULL)
        {
            perror("Memory allocation failed");
            for (int j = 0; j < i; ++j)
            {
                free(matrix[j]);
            }
            free(matrix);
            fclose(fp);
            return;
        }
    }

    char word[50];
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (fscanf(fp, "%d", &matrix[i][j]) != 1)
            {
                perror("Error reading matrix element");
                fclose(fp);
                for (int k = 0; k < rows; ++k)
                {
                    free(matrix[k]);
                }
                free(matrix);
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
    int col2 = atoi(strtok(NULL, "X"));

    int **matrix2 = (int **)malloc(rows2 * sizeof(int *));
    for (int i = 0; i < rows2; ++i)
    {
        matrix2[i] = (int *)malloc(col2 * sizeof(int));
        if (matrix2[i] == NULL)
        {
            perror("Memory allocation failed");
            for (int j = 0; j < i; ++j)
            {
                free(matrix2[j]);
            }
            free(matrix2);
            fclose(fp);
            return;
        }
    }

    for (int i = 0; i < rows2; ++i)
    {
        for (int j = 0; j < col2; ++j)
        {
            if (fscanf(fp, "%d", &matrix2[i][j]) != 1)
            {
                perror("Error reading matrix element");
                fclose(fp);
                for (int k = 0; k < rows2; ++k)
                {
                    free(matrix2[k]);
                }
                free(matrix2);
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

    fclose(fp);

    // Print the matrix
    printf("Matrix:\n");
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Matrix2:\n");
    for (int i = 0; i < rows2; ++i)
    {
        for (int j = 0; j < col2; ++j)
        {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }

    int **Result = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i)
    {
        Result[i] = (int *)malloc(col2 * sizeof(int));
        if (Result[i] == NULL)
        {
            perror("Memory allocation failed");
            for (int j = 0; j < i; ++j)
            {
                free(Result[j]);
            }
            free(Result);
            return;
        }
    }

    if (col == rows2)
    {
        pthread_t *threads = (pthread_t *)malloc(rows * sizeof(pthread_t));

        for (int i = 0; i < rows; i++)
        {
            // Create a unique initialize structure for each thread
            struct my *initialize = (struct my *)malloc(sizeof(struct my));
            initialize->matrix1 = matrix;
            initialize->matrix2 = matrix2;
            initialize->result = Result;
            initialize->matrix_1_row = rows;
            initialize->matrix_1_col = col;
            initialize->matrix_2_row = rows2;
            initialize->matrix_2_col = col2;
            initialize->curr_row = i;

            // // Print the matrices for verification
            // printf("Matrix1:\n");
            // for (int i = 0; i < rows; ++i)
            // {
            //     for (int j = 0; j < col; ++j)
            //     {
            //         printf("%d ", initialize->matrix1[i][j]);
            //     }
            //     printf("\n");
            // }

            // printf("Matrix2:\n");
            // for (int i = 0; i < rows2; ++i)
            // {
            //     for (int j = 0; j < col2; ++j)
            //     {
            //         printf("%d ", initialize->matrix2[i][j]);
            //     }
            //     printf("\n");
            // }

            // Create the thread with the unique initialize structure
            pthread_create(&threads[i], NULL, multiplyIt, (void *)initialize);
        }

        // Wait for all threads to finish
        for (int i = 0; i < rows; i++)
        {
            pthread_join(threads[i], NULL);
        }

        // Print the final result
        printf("Result:\n");
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < col2; ++j)
            {
                printf("%d ", Result[i][j]);
            }
            printf("\n");
        }
    // printf("RUn through here \n");

    }
}

int main()
{
    call_read_and_calc("/home/hamad/Desktop/PdcAssignment1/inputFIle.txt");
    return 0;
}
