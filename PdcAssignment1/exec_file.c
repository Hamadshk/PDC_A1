#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define OPCODE_MAX 10

int main()
{
    FILE *file = fopen("inputFIle.txt", "r");

    char buffer[OPCODE_MAX];
    fscanf(file, "%s", buffer);
    int opcode;
    opcode = atoi(buffer);
    if (opcode == 1)
    {
        char *args[] = {"python3", "runPythonBased.py", NULL};
        execvp(args[0], args);
    }

    else if (opcode == 2)
    {
        char *args[] = {"java", "runJavaBased", NULL};
        execvp(args[0], args);
    }
    else if (opcode == 3)
    {
        char *args[] = {"./a.out", NULL};
        execvp(args[0], args);
    }
    else if (opcode == 4)
    {
        char *args[] = {"./b.out", NULL};//run thorugh vec instruction
        execvp(args[0], args);
    }
    else if (opcode == 5)
    {
        char *args[] = {"./c", NULL};//run thorugh pthread instruction
        execvp(args[0], args);
    }
    else if (opcode == 5)
    {
        char *args[] = {"./c", NULL};//run thorugh pthread instruction and vec instr
        execvp(args[0], args);
    }
    else
    {
        printf("Invalid OPCODE!!!");
    }

    fclose(file);
}