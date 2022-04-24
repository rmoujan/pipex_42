/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:20:25 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/24 00:15:25 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/libft.h"
#include "../gnl/get_next_line.h"
//handle multiple pipes :
void	ft_error(char *str)
{
	perror(str);
	exit(1);
}

void	ft_exit(void)
{
	write(1, "ERROR MANAGEMENT\n", 17);
	exit(1);
}

void	herdoc_main1(char *argv[], char *const envp[], t_arg *prg2, t_arg *prg1)
{
	getting_paths(envp, prg1);
	concaten_pathscmd(prg1, argv[3]);
	getting_paths(envp, prg2);
	concaten_pathscmd(prg2, argv[4]);
}

void	open_file(t_fds	*id, char *argv[])
{
	id->fd2 = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (id->fd1 == -1 || id->fd2 == -1)
		ft_exit();
}

int	main(int argc, char *argv[], char *const envp[])
{
	t_arg	*prg1;
	t_arg	*prg2;
	t_fds	id;

	id.prg = NULL;
	if (strcmp(argv[1], "here_doc\0") == 0)
	{
		errors_heredoc(argc);
		prg1 = (t_arg *) malloc (sizeof(t_arg));
		prg2 = (t_arg *) malloc (sizeof(t_arg));
		herdoc_main1(argv, envp, prg2, prg1);
		open_file(&id, argv);
		get_input_herdoc(&id, argv[2]);
		forking_heredoc(id, prg1, prg2, envp);
	}
	else
	{
		checks_errormltpipe(argc);
		id.prg = (t_arg **)malloc(sizeof(t_arg *) * (argc - 3) + 1);
		id.pii = (int **) malloc(sizeof(int *) * (argc - 4));
		mlt_pipes2(argc, argv, envp, id);
	}
	return (0);
}
