/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multpipes_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:58:10 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/23 04:50:09 by rmoujan          ###   ########.fr       */
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

void	mlt_pipes1(int argc, char *argv[], char *const envp[], t_fds id)
{
	getting_paths_bns(envp, id.prg);
	concaten_pathscmd_bns(id.prg, argv);
	id.argc = argc;
	multpipes_chunk1(id, argv, envp);
}

void	mlt_pipes2(int argc, char *argv[], char *const envp[], t_fds id)
{
	int	i;

	i = 0;
	while (i < (argc - 4))
		id.pii[i++] = (int *)malloc(sizeof(int) * 2);
	i = 0;
	while (i < (argc - 3))
		id.prg[i++] = (t_arg *)malloc(sizeof(t_arg));
	id.prg[i] = NULL;
	mlt_pipes1(argc, argv, envp, id);
}
