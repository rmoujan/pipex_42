// int main()
// {
//     int n;
//     int filedes[2];
//     char buffer[1025];
//     char *message = "Hello, World!";

//     pipe(filedes);
//     write(filedes[1], message, strlen(message));

//     if ((n = read ( filedes[0], buffer, 1024 ) ) >= 0) {
//         buffer[n] = 0;  //terminate the string
//         printf("read %d bytes from the pipe: %s\n", n, buffer);
//     }  
//     else
//         perror("read");
//     exit(0);
// }

#include "pipex.h"

int main(int argc, char *argv[], char *envp[])
{
  int id = fork();
  if (argc > 1)
  {
    if (id == -1)
      perror("ERROR FORK\n");
    if (id == 0)
    {
           if (execve(argv[1], argv + 1, envp) == -1)
         perror("execve");
    }
    else{
      wait(NULL);
      printf("HALLO\n");
    }
    // if(id != 0)
    //   wait(NULL);
  //printf("My pid is: %d\n", getpid());
  }
  return 0;
}
// // int main()
// // {
// //     int fd1 = open("test.txt", O_WRONLY | O_APPEND);
// //     int fd2 = dup2(fd1, 2);
// //     printf("FD1 IS %D AND FD2 IS %D", fd1, fd2);
// //     write(fd1, "Hallo WORLD\n", 12);
// //     write(fd2, "This is me Reshe\n", 17);
    
// // }
// void doWork(){
// 	fork();
// 	fork();
// 	printf("Hello world!\n");
// }
// int main() {
// 	doWork();
// 	printf("Hello world!\n");
// 	return (0);
// }
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>
// // #include <unistd.h>
// // #include <sys/wait.h>

// // int main(void) {
// //     fork();
// //     printf("1\n");
// //     fork();
// //     printf("2\n");
// // }
// // //output :
// // // 1
// // // 2
// // // 1
// // // 2
// // // 2                                                                                     
// // // 2