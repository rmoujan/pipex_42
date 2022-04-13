/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:20:25 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/13 12:09:23 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//handle multiple pipes :
void	ft_error(char *str)
{
	perror(str);
	exit(1);
}
int main(int argc, char *argv[])
{
	int i;
	int pid;
	int pid2[argc - 5];
    int fd[argc - 4][2];
    
	i = 0; 
	//creation of the pipe:
    while (i < (argc - 4))
    {
        if (pipe(fd[i]) == -1)
            ft_error("pipe");
		//printf("test\n");
		i++;
	}
	i = 0;
	pid = fork();
	if (pid < 0)
		 ft_error("fork");
	else if (pid == 0)
	{
		//first child process :
		printf("first child process \n");
		
	}
	else
	{
		//parent process :
		while (i < (argc - 5))
		{
			pid2[i] = fork();
			if (pid2[i] < 0)
				ft_error("fork");
			if (pid2[i] == 0)
			{
				printf("process number %d\n", i);		
			}
			i++;
		}
	}
	return (0);
}