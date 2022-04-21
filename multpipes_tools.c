/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multpipes_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:58:10 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/21 15:59:43 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"

void	close_mltpipes1(t_fds id, int i)
{
	int	j;

	j = 0;
	while (j < (id.argc - 4))
	{
		if (j != (i - 1))
			close(id.pii[j][0]);
		if (j != i)
			close(id.pii[j][1]);
		j++;
	}			
}
