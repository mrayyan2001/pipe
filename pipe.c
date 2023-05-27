#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        printf("Failed to create pipe.\n");
        return 1;
    }

    int id = fork();
    if (id == -1)
    {
        printf("Failed to create process.\n");
        return 4;
    }
    else if (id == 0) // child
    {
        int x;
        printf("Enter a number: ");
        scanf("%d", &x);
        close(fd[0]);
        if (write(fd[1], &x, sizeof(int)) == -1)
        {
            printf("An error ocurred with writing to the pipe.\n");
            return 2;
        }
        close(fd[1]);
    }
    else // parent
    {
        int y;
        close(fd[1]);
        if (read(fd[0], &y, sizeof(int)) == -1)
        {
            printf("An error ocurred with reading from the pipe.\n");
            return 3;
        }
        close(fd[0]);
        printf("Got from child process %d\n", y);
    }

    return 0;
}