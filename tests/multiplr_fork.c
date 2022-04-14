/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplr_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:12:31 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/14 11:57:31 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../pipex.h"

int main(int argc, char *argv[])
{
    //creating multiple processes :
    int pid;
    int pi[3];
    int i = 0;

    for(int i=0;i<6;i++) // loop will run n times (n=5)
    {
        if(fork() == 0)
        {
            //printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            exit(0);
        }
    }
    
    for(int i=0;i<2;i++) // loop will run n times (n=5)
        wait(NULL);
printf("afer loop \n");
    // pid = fork();

    // if (pid < 0)
    //     perror("fork");
    // else if(pid == 0)
    // {
    //     //first child process :
    //     printf("[son] pid %d from [parent] pid %d\n", getpid(), getppid());
    // }
    // else
    // {
    //     while (i < 3)
    //     {
    //         pi[i] = fork();
    //         if (pi[i] == 0)
    //             printf("[son] pid %d from [parent] pid %d\n", getpid(), getppid());
    //         i++;
    //     }
    //     // printf("parent process %d\n", getppid());
    // }
}