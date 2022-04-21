/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:20:25 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/21 18:55:13 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"

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
void herdoc_main(char *argv[], char *const envp[], t_arg	*prg2, t_arg	*prg1)
{
			
		getting_paths(envp, prg1);
		concaten_pathscmd(prg1, argv[3]);
	
		getting_paths(envp, prg2);
		concaten_pathscmd(prg2, argv[4]);
		check_exist_cmd(prg1, prg2);

}
int	main(int argc, char *argv[], char *const envp[])
{
	t_fds	id;
	t_arg	*prg1;
	t_arg	*prg2;
	
	if (strcmp(argv[1], "here_doc\0") == 0)
	{
		//ft_heredoc(argc, argv, envp);
		errors_heredoc(argc);
		prg1 = (t_arg *) malloc(sizeof(t_arg));
		//getting_paths(envp, prg1);
		//concaten_pathscmd(prg1, argv[3]);
		prg2 = (t_arg *) malloc(sizeof(t_arg));
		//getting_paths(envp, prg2);
		//concaten_pathscmd(prg2, argv[4]);
		//check_exist_cmd(prg1, prg2);
		herdoc_main(argv, envp,prg2, prg1);
		id.fd2 = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (id.fd1 == -1 || id.fd2 == -1)
			ft_exit();
		get_input_herdoc(&id, argv[2]);
		forking_heredoc(id, prg1, prg2, envp);
	}
	else
	{
			int		i;
	t_fds	id;

	i = 0;
	checks_errormltpipe(argc);
	id.prg = (t_arg **)malloc(sizeof(t_arg *) * (argc - 3) + 1);
	id.pii = (int **) malloc(sizeof(int *) * (argc - 4));
	while (i < (argc - 4))
	{
		id.pii[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	while (i < (argc - 3))
	{
		id.prg[i] = (t_arg *)malloc(sizeof(t_arg));
		i++;
	}
	id.prg[i] = NULL;
	getting_paths_bns(envp, id.prg);
	concaten_pathscmd_bns(id.prg, argv);
	check_exist_cmdbns(id.prg);
	id.argc = argc;
	multpipes_chunk1(id, argv, envp);
		// multiple_pipe(argc, argv, envp);
	}
		
	while(1)
	{
		
	}
	return (0);
}
