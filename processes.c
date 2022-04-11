/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:42:24 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/11 11:00:14 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_process(t_fds id, t_arg *prg1, char *const envp[])
{
	// if (dup2(id.fd1, 0) == -1)
	// {
	// 	perror("dup2");
	// 	exit(1);
	// }
	// close(id.fd1);
	// close(id.pi[0]);
	// if (dup2(id.pi[1], 1) == -1)
	// {
	// 	perror("dup2");
	// 	exit(1);
	// }
	// close(id.pi[1]);
	// if (execve(prg1->path[0], prg1->cmd, envp) == -1)
	// {
	// 	perror("execve");
	// 	exit(1);
	// }
	//
	    printf("child 1 \n");
		if (dup2(id.fd1, 0) == -1)
        {
            perror("dup2");
            exit(1);
        }
		close(id.fd1);
        close(id.pi[0]);
        if (dup2(id.pi[1], 1) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(id.pi[1]);
        if (execve(prg1->path[0], prg1->cmd, envp) == -1)
		{
			perror("execve");
			exit(1);
		}
}

void	second_process(t_fds id, t_arg *prg2, char *const envp[])
{
	// int	status;

	// waitpid(id.frk1, &status, 0);
	// close(id.pi[1]);
	// if (dup2(id.pi[0], 0) == -1)
	// {
	// 	perror("dup2");
	// 	exit(1);
	// }
	// close(id.pi[0]);
	// if (dup2(id.fd2, 1) == -1)
	// {
	// 	perror("dup2");
	// 	exit(1);
	// }
	// close(id.fd2);
	// if (execve(prg2->path[0], prg2->cmd, envp) == -1)
	// {
	// 	perror("execve");
	// 	exit(1);
	// }

	            printf("childd 2\n");
            close(id.pi[1]);
            if (dup2(id.pi[0], 0) == -1)
            {
                perror("dup2");
                exit(1);
            }
            close(id.pi[0]);
            if (dup2(id.fd2, 1) == -1)
            {
                perror("dup2");
                exit(1);
            }
            close(id.fd2);
            if (execve(prg2->path[0], prg2->cmd, envp) == -1)
			{
                perror("execve");
				exit(1);
			}
}

void	begin_forking(t_fds id, t_arg *prg1, t_arg *prg2, char *const envp[])
{
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
	if (pipe(id.pi) < 0)
		ft_exit();
	id.frk1 = fork();
	if (id.frk1 < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (id.frk1 == 0)
		first_process(id, prg1, envp);
	else
	{
		id.frk2 = fork();
		if (id.frk2 < 0)
		{
			perror("fork");
			exit(1);
		}
		else if (id.frk2 == 0)
			second_process(id, prg2, envp);
	}
}
