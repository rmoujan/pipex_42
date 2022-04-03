#include "pipex.h"

int main(int argc, char *argv[])
{
    int id;
    int r;
    int fd[2];
    char *buffer;
    int file;

    file = open("file3.txt",O_RDWR | O_APPEND);
    
    if (pipe(fd) == -1)
    {
      printf("error \n");
      return 1;
    }

    id = fork();
    if (id < 0)
        perror("ERROR");
    
    //child process :
    else if (id == 0)
    {
        //should do here the first execeve function to execute the cmd1
        close(fd[0]);
        if (dup2(fd[1], 1) == -1)
            perror("dup2");
        close(fd[1]);
         if (execve(argv[1], argv + 1, NULL) == -1)
                perror("execve");
    }

    //parent process :
    else
    {
        //we will wait until the child process finish (for bringing the data from C.process!!)
        //should do here the second execeve function to execute the cmd2
        wait(NULL);
        close(fd[1]);
        buffer = get_next_line(fd[0]);
        while (buffer)
        {
            printf("buffer is %s\n",buffer);
            write(file, buffer, strlen(buffer));
            free(buffer);
            buffer = get_next_line(fd[0]);
        }
        close(fd[0]);
       printf("Hallo from parent process\n");

    }    
    return (0);
}