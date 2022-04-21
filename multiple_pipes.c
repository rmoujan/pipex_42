/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:22:53 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/21 01:18:02 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void close_mltpipes1(int **pi, int argc, int i)
{
	int j;

	j = 0;
	while (j < (argc - 4))
	{
		if (j != (i - 1))
			close(pi[j][0]);
					
		if (j != i)
			close(pi[j][1]);
		j++;
	}
}

// void while_mltpipes(int **pi, t_fds id, t_arg **prg, char *const envp[])
// {

// 	id.frk1 = fork();
// 	if(id.frk1 < 0)
// 		ft_error("fork");
// 	else if (id.frk1  == 0)
// 	{
// 		close_mltpipes1(pi, argc, i);
//         if (i == 0)
//         {
// 			if (dup2(id.fd1, 0) == -1)
// 				ft_error("dup2");
//             close(id.fd1);
//         }
//         else if (i != 0)
//         {
// 			if (dup2(pi[i - 1][0], 0) == -1)
// 				ft_error("dup2");
//         }
//         if (i == (argc - 4))
//         {
// 			if (dup2(id.fd2, 1) == -1)
// 				ft_error("dup2");
//         }
//         else if (i != (argc - 4))
// 		{
// 			if (dup2(pi[i][1], 1) == -1)
// 				ft_error("dup2");
//         }
// 		if (execve(prg[i]->path[0], prg[i]->cmd, envp) == -1)
// 			ft_error("execve");
// 	}
// }

void close_mltpipes2(int **pi, t_fds id, int argc)
{
	int i;
	
	i = 0;
	while (i < (argc - 4))
	{
		close(pi[i][0]);
		close(pi[i][1]);
		i++;
	}
    close(id.fd1);
	close(id.fd2);
}

void forking_mltpipes(int **pi, int argc, t_arg **prg, char *const envp[])
{
	int j;
	int i;
	t_fds id;

	j = 0;
	i = 0;
	id.fd1 = open(argv[1], O_RDWR | O_CREAT, 0666);
	id.fd2 = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
	id.frk1 = fork();
	if(id.frk1 < 0)
		ft_error("fork");
	else if (id.frk1 == 0)
		{
			while (i < (argc - 3))
			{
					id.frk1 = fork();
	if(id.frk1 < 0)
		ft_error("fork");
	else if (id.frk1  == 0)
	{
		close_mltpipes1(pi, argc, i);
        if (i == 0)
        {
			if (dup2(id.fd1, 0) == -1)
				ft_error("dup2");
            close(id.fd1);
        }
        else if (i != 0)
        {
			if (dup2(pi[i - 1][0], 0) == -1)
				ft_error("dup2");
        }
        if (i == (argc - 4))
        {
			if (dup2(id.fd2, 1) == -1)
				ft_error("dup2");
        }
        else if (i != (argc - 4))
		{
			if (dup2(pi[i][1], 1) == -1)
				ft_error("dup2");
        }
		if (execve(prg[i]->path[0], prg[i]->cmd, envp) == -1)
			ft_error("execve");
	}
				// while_mltpipes(pi, id, prg, envp);
				i++;
			}//end while
		}//end else
        if (waitpid(-1, NULL, 0) == -1)
			ft_error("waitpid");
		close_mltpipes2(pi, id, argc);
}

void chunk_mltpipe(int argc, t_arg **prg, char *const envp[])
{
	int **pi; 
    int i;
    
	i = 0;
	pi = (int **) malloc(sizeof(int *) * (argc - 4));
	while (i < (argc - 4))
	{
		pi[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
    while (i < (argc - 4))
    {
        if (pipe(pi[i]) == -1)
            ft_error("pipe");
		i++;
	}
	forking_mltpipes(pi, argc, prg, envp);
}

void multiple_pipe(int argc, char *argv[], char *const envp[])
{
    int i;
	t_arg **prg;

	i = 0;
	printf("starting multipipes \n");
    checks_error_bns(argc);
	prg = (t_arg **)malloc(sizeof(t_arg *) * (argc - 3) + 1);
	while (i < (argc - 3))
	{
		prg[i] = (t_arg *)malloc(sizeof(t_arg));
		i++;
	}
	prg[i]= NULL;
	getting_paths_bns(envp, prg);
	concaten_pathscmd_bns(prg, argv);
	check_exist_cmdbns(prg);
    chunk_mltpipe(prg, argc, argv, envp);
}