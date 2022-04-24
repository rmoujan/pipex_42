/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:41:58 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/24 01:55:00 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/libft.h"
#include "../gnl/get_next_line.h"

void	first_process(t_fds id, t_arg *prg1, char *const envp[])
{	
	close(id.pidoc[0][1]);
	close(id.pidoc[1][0]);
	if (dup2(id.pidoc[0][0], 0) == -1)
	{
		printf("first dup \n");
		ft_error("dup2");
	}
	close(id.pidoc[0][0]);
	if (dup2(id.pidoc[1][1], 1) == -1)
		ft_error("dup2");
	close(id.pidoc[1][1]);
	if (execve(prg1->path[0], prg1->cmd, envp) == -1)
	{
		perror("execve");
		exit(1);
	}
}

void	second_process(t_fds id, t_arg *prg2, char *const envp[])
{
	close(id.pidoc[1][1]);
	close(id.pidoc[0][0]);
	close(id.pidoc[0][1]);
	if (dup2(id.pidoc[1][0], 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(id.pidoc[1][0]);
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

void	forking_heredoc(t_fds id, t_arg *prg1, t_arg *prg2, char *const envp[])
{
	if (pipe(id.pidoc[1]) < 0)
		ft_exit();
	id.frk1 = fork();
	if (id.frk1 < 0)
		ft_error("fork");
	else if (id.frk1 == 0)
		first_process(id, prg1, envp);
	else
	{
		id.frk2 = fork();
		if (id.frk2 < 0)
			ft_error("fork");
		else if (id.frk2 == 0)
			second_process(id, prg2, envp);
		else
			close_heredoc(id);
	}
}

void	close_heredoc(t_fds id)
{
	int	k;

	k = 0;
	while (k < 2)
	{
		close(id.pidoc[k][1]);
		close(id.pidoc[k][0]);
		k++;
	}
	close(id.fd1);
	close(id.fd2);
	if (waitpid(-1, NULL, 0) == -1)
		perror("waitpid");
	if (waitpid(-1, NULL, 0) == -1)
		perror("waitpid");
}
