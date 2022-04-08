/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testdup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:34:51 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/08 13:54:35 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"


// //there is a problem in dup2 ..  does not work as expected
// int main(int argc, char *argv[])
// {
//     int fd;
//     char *path = "/bin/cat";
//     char *args[] = {path, "cat", NULL};
//     fd = open(argv[1], O_RDONLY);
//     if (fd == -1)
//         printf("error \n");
//     if (dup2(fd, 0) == -1)
//         perror("dup2");
//     close(fd);
//     if (execve("/bin/cat", args + 1, NULL) == -1)
//         perror("execve");
//     printf("should not excute\n");
//     return (0);
// }

#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
  
int main(int argc, char *argv[])
{
    int file_desc = open(argv[1],O_WRONLY | O_APPEND);
      
    // here the newfd is the file descriptor of stdout (i.e. 1)
    dup2(file_desc, 1) ; 
          
    // All the printf statements will be written in the file
    // "tricky.txt"
    printf("I will be printed in the file tricky.txt\n");
      
return 0;
}