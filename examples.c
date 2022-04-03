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
        if (dup2(fd[1], 1) == -1)
            perror("dup2");
         if (execve(argv[1], argv + 1, NULL) == -1)
                perror("execve");
    }

    //parent process :
    else
    {
        //we will wait until the child process finish (for bringing the data from C.process!!)
        //should do here the second execeve function to execute the cmd2
        wait(NULL);
        buffer = get_next_line(fd[0]);
       // printf("%s \n", buffer);
        int i = 0;
        while (buffer)
        {
            //printf("%d\n", i);
            //printf("buffer is %s and strlen(buffer) is %zu\n",buffer, strlen(buffer));
            write(file, buffer, strlen(buffer));
            free(buffer);
            buffer  = NULL;
            buffer = get_next_line(fd[0]);
            i++;
        }
       printf("Hallo from parent process\n");
       // printf("%s \n", buffer);
    }    
    return (0);
}