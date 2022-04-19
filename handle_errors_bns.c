/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bns.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:22:36 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/19 17:31:37 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"

void	ft_checkbns(t_arg **prg)
{
	int	i;
    int j;

	i = 0;
    j = 0;
    while (prg[j])
    {
        if (ft_strcmp(prg[j]->cmd[0], "grep\0") == 0)
	    {
		    while (prg[j]->cmd[i])
		    {
			    if (prg[j]->cmd[i][0] == '\'')
			    {
				    if (ft_calcul(prg[j]->cmd[i]) == 1)
				    {
					    prg[j]->cmd[i] = ft_strtrim(prg[j]->cmd[i], "'\0");
				    }
				    else
				    {
					    ft_exit();
				    }
			    }
			i++;
		    }
	    }
        j++;  
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
