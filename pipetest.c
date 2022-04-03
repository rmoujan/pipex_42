#include "pipex.h"

int main(int argc, char *argv[])
{


    int fr;
    int fd[2];
    char *buffer;
    int size = strlen(argv[1]);
    buffer = malloc(size * sizeof(char));
    if (pipe(fd) == -1)
        perror("Error pipe");
    fr = fork();
    if (fr == -1)
        perror("Error Fork");
    else if (fr == 0)
    {
        close(fd[0]);
        write(fd[1], argv[1], size);
        close(fd[1]);

        //child process 
        //should send a string to parent process

    }
    else{
         wait(NULL);
        // close(fd[1]);
        // read(fd[0], buffer, size);
        // close(fd[0]);
        // printf("buffer is %s", buffer);

    char          buffer[1024];
    int           ret;

    while ((ret = read(fd[0], buffer, 1023)))
    {
        buffer[ret] = 0;
        printf("%s\n", buffer);
    }

        //printf("parent process \n");
        //parent process
        //should here recieve a string fron child process

    }
    return (0);
}

// #include <unistd.h>
// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <string.h>

// int
// main(int argc, char *argv[], char *env[])
// {
//   pid_t          pid;
//   int            status;
//   int            pipe_fd[2];

//   if (argc < 2)
//     return 1;

//   if (pipe(pipe_fd) == -1)
//     {
//       perror("pipe");
//       return 1;
//     }

//   if ((pid = fork()) == -1)
//     {
//       perror("fork");
//       return 1;
//     }
//   else if (pid == 0)
//     {
//       close(pipe_fd[0]);
//       write(pipe_fd[1], argv[1], strlen(argv[1]));
//       close(pipe_fd[1]);
//       return 1;
//     }
//   else
//     {
//       char          buffer[1024];
//       int           ret;

//       close(pipe_fd[1]);
//       while ((ret = read(pipe_fd[0], buffer, 1023)))
//         {
//           buffer[ret] = 0;
//           printf("%s\n", buffer);
//         }
//       close(pipe_fd[0]);
//     }

//   return 0;
// }
 
