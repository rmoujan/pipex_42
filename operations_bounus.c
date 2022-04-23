/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_bounus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:29:26 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/23 04:44:09 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"

void	checks_errormltpipe(int argc)
{
	if (argc < 5)
	{
		write(1, "ERROR MANAGEMENT \n", 18);
		exit(1);
	}
}

void	chunk_concat_cmd(t_arg **prg, int k)
{
	int	i;

	i = 0;
	if (check_script(prg[k]) == 1 || check_file(prg[k]) != -1)
	{
		free(prg[k]->path[0]);
		prg[k]->path[0] = ft_strdup(prg[k]->cmd[0]);
	}
	else
	{
		ft_checkbns(prg);
		i = 0;
		while (prg[k]->path[i])
		{
			prg[k]->path[i] = ft_strjoin(prg[k]->path[i], "/\0");
			prg[k]->path[i] = ft_strjoin(prg[k]->path[i], prg[k]->cmd[0]);
			i++;
		}	
		check_exist_cmdbns(prg[k]);
	}
}

void	concaten_pathscmd_bns(t_arg **prg, char **argv)
{
	int	j;
	int	k;

	j = 0;
	k = 2;
	while (prg[j])
	{
		prg[j]->cmd = ft_split(argv[k], ' ');
		j++;
		k++;
	}
	k = 0;
	while (prg[k])
	{
		chunk_concat_cmd(prg, k);
		k++;
	}
}

void	getting_paths_bns(char *const envp[], t_arg **prg)
{
	int	i;
	int	j;
	int	flag;

	j = 0;
	i = 0;
	flag = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			while (prg[j])
			{
				prg[j]->path = ft_split(envp[i], ':');
				prg[j]->path[0] = ft_strtrim(prg[j]->path[0], "PATH=");
				flag = 1;
				j++;
			}
			break ;
		}
		i++;
	}
	if (flag == 0)
		exit(1);
}

void	check_exist_cmdbns(t_arg *prg)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (prg->path[i])
	{
		if (access(prg->path[i], F_OK) != -1)
		{
			free(prg->path[0]);
			prg->path[0] = prg->path[i];
			break ;
		}
		i++;
	}
}
