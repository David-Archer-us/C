#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct Raw
{
    int n;
    double total;
} data;

void average (int n, int fd[][2], char *argv[]) {
    if (n == 0) return;
    int pid = fork();
    if (pid == 0) {
        average(n - 1, fd, argv);
        FILE *inputFile = fopen(argv[n], "r");
        if (inputFile == NULL)
        {
            printf("avg.many: cannot open file\n");
            exit(1);
        }
        double subtotal = 0, buffer;
        int i = 0;
        while (fscanf(inputFile, "%lf", &buffer) != EOF) {
            subtotal += buffer;
            i++;
        }
        data d;
        d.total = subtotal;
        d.n = i;
        write(fd[n][1], &d, sizeof(d));
        fclose(inputFile);
        exit(0);
    } else wait(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) exit(0);
    int numF = argc -1;
    int fd[argc][2];

    for (int i = 1; i <= numF; i++)
    {
        pipe(fd[i]);
    }
    average(numF, fd, argv);
    double total = 0;
    int numN = 0;
    for (int i = 1; i <= numF; i++)
    {
        data d;
        read(fd[i][0], &d, sizeof(d));
        total += d.total;
        numN += d.n;
    }
    double result = 0;
    if (numN != 0) result = total / numN;
    printf("%.4lf\n", result);
    return 0;
}
