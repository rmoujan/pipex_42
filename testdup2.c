/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testdup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:34:51 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/05 15:36:03 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


//there is a problem in dup2 ..  does not work as expected
int main(int argc, char *argv[])
{
    int fd;
    char *path = "/bin/cat";
    char *args[] = {path, "cat", NULL};
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        printf("error \n");
    if (dup2(fd, 0) == -1)
        perror("dup2");
    close(fd);
    if (execve("/bin/cat", args + 1, NULL) == -1)
        perror("execve");
    printf("should not excute\n");
    return (0);
}