#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

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

void *multiplyIt(void *bigbox)
{
    struct my *myData = (struct my *)bigbox;
    int save = myData->curr_row;
    // printf("Save is %d \n ", save);
    for (int j = 0; j < myData->matrix_2_col; j++)
    {
        int sum = 0;
        for (int k = 0; k < myData->matrix_2_row; k++)
        {
            sum += myData->matrix1[save][k] * myData->matrix2[k][j];
        }
        // printf("result of index i %d and index j is %d with sum %d \n ", save, j, sum);
        myData->result[save][j] = sum;
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

            pthread_create(&threads[i], NULL, multiplyIt, (void *)initialize);
        }

        for (int i = 0; i < rows; i++)
        {
            pthread_join(threads[i], NULL);
        }

        printf("Result:\n");
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < col2; ++j)
            {
                printf("%d ", Result[i][j]);
            }
            printf("\n");
        }
    }
}

int main()
{
    call_read_and_calc("/home/hamad/Desktop/PdcAssignment1/inputFIle.txt");
    return 0;
}
