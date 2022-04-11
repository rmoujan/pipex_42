/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:45:24 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/11 14:58:52 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	ft_check(t_arg *prg)
{
	int	i;

	i = 0;
	if (ft_strcmp(prg->cmd[0], "grep\0") == 0)
	{
		while (prg->cmd[i])
		{
			if (prg->cmd[i][0] == '\'')
			{
				if (ft_calcul(prg->cmd[i]) == 1)
				{
					prg->cmd[i] = ft_strtrim(prg->cmd[i], "'\0");
				}
				else
				{
					ft_exit();
				}
			}
			i++;
		}
	}
}

int	calcul_chunks(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			counter++;
		else
			break ;
		i++;
	}
	return (counter);
}

int	ft_calcul(char *str)
{
	int	i;
	int	counter2;

	i = 0;
	counter2 = 0;
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == '\'')
			counter2++;
		else
			break ;
		i--;
	}
	if (calcul_chunks(str) == counter2)
		return (1);
	else
		return (0);
}
