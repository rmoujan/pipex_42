/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:28:17 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/11 15:06:02 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	checks_errors(int argc)
{
	if (argc != 5)
	{
		write(1, "ERROR MANAGEMENT \n", 18);
		exit(1);
	}
}

void	test_files(char *argv[])
{
	if (access(argv[1], F_OK) == -1
		|| access(argv[1], R_OK | W_OK | X_OK) == -1)
	{
		write(1, "ERROR OCCURED WHEN CHECKING FILES \n", 35);
		exit(1);
	}
	if (access(argv[4], F_OK) == -1
		|| access(argv[4], R_OK | W_OK | X_OK) == -1)
	{
		write(1, "ERROR OCCURED WHEN CHECKING FILES \n", 35);
		exit(1);
	}
}

void	check_exist_cmd(t_arg *prg1, t_arg *prg2)
{
	int	i;

	i = 0;
	while (prg1->path[i])
	{
		if (access(prg1->path[i], F_OK) != -1)
		{
			free(prg1->path[0]);
			prg1->path[0] = prg1->path[i];
			break ;
		}
		i++;
	}
	i = 0;
	while (prg2->path[i])
	{
		if (access(prg2->path[i], F_OK) != -1)
		{
			free(prg2->path[0]);
			prg2->path[0] = prg2->path[i];
			break ;
		}
		i++;
	}
}

void	ft_close(t_fds id)
{
	close(id.pi[0]);
	close(id.pi[1]);
	close(id.fd1);
	close(id.fd2);
	waitpid(id.frk1, NULL, 0);
	waitpid(id.frk2, NULL, 0);
}
