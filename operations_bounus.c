/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_bounus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:29:26 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/14 17:43:52 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	checks_error_bns(int argc)
{
	if (argc < 5)
	{
		write(1, "ERROR MANAGEMENT \n", 18);
		exit(1);
	}
}

void	concaten_pathscmd_bns(t_arg **prg, char **argv)
{
	int	i;
	int j;
	int k;

	j = 0;
	k = 2;
	while (prg[j])
	{
		prg[j]->cmd = ft_split(argv[k], ' ');	
		j++;
		k++;
	}
	ft_check(prg);
	j = 0;
	while (prg[j])
	{
		i = 0;
		while (prg[j]->path[i])
		{
			prg[j]->path[i] = ft_strjoin(prg[j]->path[i], "/\0");
			prg[j]->path[i] = ft_strjoin(prg[j]->path[i], prg[j]->cmd[0]);
			i++;
		}
		j++;
	}
}

void	getting_paths_bns(char *const envp[], t_arg **prg)
{
	int	i;
	int j;

	j = 0;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			while (prg[j])
			{
				prg[j]->path = ft_split(envp[i], ':');
				prg[j]->path[0] = ft_strtrim(prg[j]->path[0], "PATH=");
				j++;
			}
			break;
		}
		i++;
	}	
}

void	check_exist_cmdbns(t_arg **prg)
{
	int	i;
	int j;

	j = 0;
	while (prg[j])
	{
		i = 0;
		while (prg[j]->path[i])
		{
			if (access(prg[j]->path[i], F_OK) != -1)
			{
				free(prg[j]->path[0]);
				prg[j]->path[0] = prg[j]->path[i];
				break ;
			}
			i++;
		}
		j++;		
	}
}