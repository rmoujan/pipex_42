/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 02:04:41 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/22 00:15:20 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
int	check_script(t_arg *prg)
{
	int	i;
	int flag;

	i = 0;
	flag = 0;
	while (prg->path[i])
	{
		if (access(prg->path[i], F_OK) != -1)
		{
			flag = 1;
		}
		i++;
	}
	return (flag);
}
void	concaten_pathscmd(t_arg *prg, char *argv)
{
	int	i;

	i = 0;
	prg->cmd = ft_split(argv, ' ');
	check_script(prg);
	ft_check(prg);
	while (prg->path[i])
	{
		prg->path[i] = ft_strjoin(prg->path[i], "/\0");
		prg->path[i] = ft_strjoin(prg->path[i], prg->cmd[0]);
		i++;
	}
}

void	getting_paths(char *const envp[], t_arg *prg)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			prg->path = ft_split(envp[i], ':');
			prg->path[0] = ft_strtrim(prg->path[0], "PATH=");
			break ;
		}
		i++;
	}
}
