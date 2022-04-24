/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipesnew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 01:20:24 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/24 01:04:57 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/libft.h"
#include "../gnl/get_next_line.h"

void	handle_mltpipes(t_fds id, int i, char *const envp[])
{
	close_mltpipes1(id, i);
	if (i == 0)
	{
		if (dup2(id.fd1, 0) == -1)
			ft_error("dup2");
		close(id.fd1);
	}
	else if (i != 0)
	{
		if (dup2(id.pii[i - 1][0], 0) == -1)
			ft_error("dup2");
	}
	if (i == (id.argc - 4))
	{
		if (dup2(id.fd2, 1) == -1)
			ft_error("dup2");
	}
	else if (i != (id.argc - 4))
	{
		if (dup2(id.pii[i][1], 1) == -1)
			ft_error("dup2");
	}
	if (execve(id.prg[i]->path[0], id.prg[i]->cmd, envp) == -1)
		ft_error("execve");
}

void	close_mltpipes2(t_fds id)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j < (id.argc - 4))
	{
		close(id.pii[j][0]);
		close(id.pii[j][1]);
		j++;
	}
	close(id.fd1);
	close(id.fd2);
	while (k < (id.argc - 3))
	{
		if (waitpid(-1, NULL, 0) == -1)
			ft_error("waitpid");
		k++;
	}
}

void	forking_mltpipes(t_fds id, char *const envp[])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (id.argc - 3))
	{
		id.frk1 = fork();
		if (id.frk1 < 0)
			ft_error("fork");
		else if (id.frk1 == 0)
		{
			handle_mltpipes(id, i, envp);
		}
		i++;
	}
	close_mltpipes2(id);
}

void	multpipes_chunk1(t_fds id, char *argv[], char *const envp[])
{
	int	i;

	i = 0;
	id.fd1 = open(argv[1], O_RDWR);
	id.fd2 = open(argv[id.argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
	i = 0;
	while (i < (id.argc - 4))
	{
		if (pipe(id.pii[i]) == -1)
			ft_error("pipe");
		i++;
	}
	forking_mltpipes(id, envp);
}
