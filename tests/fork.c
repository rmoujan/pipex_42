#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../pipex.h"

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

// //
// int main()
// {
//   int id1;
//   int id2;

//   id1 =fork();
//   if (id1 == 0)
//     printf("child == %d\n", getpid());
//   else
//     printf("parent == %d\n", getpid());
// }

//test first example with fork:
int main()
{
  int id, id2, status;



  printf("before fork1 \n");
/*the fork start copy from this point-->*/  id = fork();

  if (id < 0)
  {
        printf("error \n");
        exit(1);
  }

    else if (id == 0)
    {
      printf("child process 1 \n");
    }
    else
    {
        waitpid(id, &status, 0);
        printf("before fork2 \n");
        id2 = fork();
        if (id2 < 0)
        {
          printf("error \n");
          exit(1);
        }
      else if (id2 == 0)
      {
        printf("child process 2 \n");
      }
      else{
        waitpid(id2, &status, 0);
        printf("parent process \n");
      }
      
    }
    printf("at the end \n");
}
//*****
// //test second example with fork
// int main()
// {
//   int id1;
//   int id2;

//   id1 = fork();
//   id2 = fork();

//   if (id1 == 0)
//   {
//     printf("first child\n");
//   }
//   else if (id1 != 0)
//   {
//     printf("first parent process\n");
//   }
//   if (id2 == 0)
//   {
//     printf("second child\n");
//   }
//   else if (id2 != 0)
//   {
//     printf("second parent process\n");
//   }
// }


// pid_t spawnChild(const char* program, char** arg_list)
// {
//     pid_t ch_pid = fork();
//     if (ch_pid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (ch_pid > 0) {
//         printf("spawn child with pid - %d\n", ch_pid);
//         return ch_pid;
//     } else {
//         execvp(program, arg_list);
//         perror("execve");
//         exit(EXIT_FAILURE);
//     }
// }

// int main(void) {
//      char *args[] = { "ls", NULL, NULL };

//     pid_t child;
//     int wstatus;

//     child = spawnChild("ls", args);

//     // if (waitpid(child, &wstatus, WUNTRACED | WCONTINUED) == -1) {
//     //     perror("waitpid");
//     //     exit(EXIT_FAILURE);
//     // }

//     exit(EXIT_SUCCESS);
// }






// /* Read characters from the pipe and echo them to stdout. */

// void read_from_pipe (int file)
// {
//   FILE *stream;
//   int c;
//   stream = fdopen (file, "r");
//   while ((c = fgetc (stream)) != EOF)
//     putchar (c);
//   fclose (stream);
// }

// /* Write some random text to the pipe. */

// void
// write_to_pipe (int file)
// {
//   FILE *stream;
//   stream = fdopen (file, "w");
//   fprintf (stream, "hello, world!\n");
//   fprintf (stream, "goodbye, world!\n");
//   fclose (stream);
// }

// int
// main (void)
// {
//   pid_t pid;
//   int mypipe[2];

//   /* Create the pipe. */
//   if (pipe (mypipe))
//     {
//       fprintf (stderr, "Pipe failed.\n");
//       return EXIT_FAILURE;
//     }

//   /* Create the child process. */
//   pid = fork ();
//   if (pid == (pid_t) 0)
//     {
//       /* This is the child process.
//          Close other end first. */
//       close (mypipe[1]);
//       read_from_pipe (mypipe[0]);
//       return EXIT_SUCCESS;
//     }
//   else if (pid < (pid_t) 0)
//     {
//       /* The fork failed. */
//       fprintf (stderr, "Fork failed.\n");
//       return EXIT_FAILURE;
//     }
//   else
//     {
//       /* This is the parent process.
//          Close other end first. */
//       close (mypipe[0]);
//       write_to_pipe (mypipe[1]);
//       return EXIT_SUCCESS;
//     }
// }
