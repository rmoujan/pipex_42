/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 02:04:41 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/23 00:47:58 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

int	check_script(t_arg *prg)
{
	int	flag;

	flag = 0;
	if (access(prg->cmd[0], F_OK) != -1)
	{
		flag = 1;
	}
	return (flag);
}

int	check_file(t_arg *prg)
{
	int	fd;

	fd = open(prg->cmd[0], O_RDWR, 0666);
	return (fd);
}

void	concaten_pathscmd(t_arg *prg, char *argv)
{
	int	i;

	i = 0;
	prg->cmd = ft_split(argv, ' ');
	if (check_script(prg) == 1 || check_file(prg) != -1)
	{
		free(prg->path[0]);
		prg->path[0] = ft_strdup(prg->cmd[0]);
	}
	else
	{
		ft_check(prg);
		while (prg->path[i])
		{
			prg->path[i] = ft_strjoin(prg->path[i], "/\0");
			prg->path[i] = ft_strjoin(prg->path[i], prg->cmd[0]);
			i++;
		}
		check_exist_cmd(prg);
	}
}

void	getting_paths(char *const envp[], t_arg *prg)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			prg->path = ft_split(envp[i], ':');
			prg->path[0] = ft_strtrim(prg->path[0], "PATH=");
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 0)
		exit(1);
}
