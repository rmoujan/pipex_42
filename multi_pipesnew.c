/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipesnew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 01:20:24 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/21 13:13:19 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"
//hena fash bghit n divider multipipes f had file  !!!!!!
void close_mltpipes1(t_fds id, int i)
{
	int j;

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
void handle_mltpipes(t_fds id, int i, char *const envp[])
{
					close_mltpipes1(id, i);
                    if (i == 0)
                    {
                        if (dup2(id.fd1, 0) == -1)
							ft_error("dup2");
                        close(id.fd1);
                    }
                    else if (i != 0)
                    {
                        if (dup2(id.pii[i - 1][0], 0) == -1)
                            ft_error("dup2");
                    }
                    if (i == (id.argc - 4))
                    {
                        if (dup2(id.fd2, 1) == -1)
                            ft_error("dup2");
                    }
                    else if (i != (id.argc - 4))
                    {
                        if (dup2(id.pii[i][1], 1) == -1)
                            ft_error("dup2");
                    }
					if (execve(id.prg[i]->path[0], id.prg[i]->cmd, envp) == -1)
						ft_error("execve");
		
}

void while_mltpipes(t_fds id, char *const envp[])
{
	int i;

	i = 0;
			while (i < (id.argc - 3))
			{
				id.frk1 = fork();
				if(id.frk1 < 0)
					ft_error("fork");
				else if (id.frk1  == 0)
				{
					handle_mltpipes(id, i, envp);
				}
				i++;
			}//end while
}

void forking_mltpipes(t_fds id, char *const envp[])
{
	int j;

	j = 0;
	id.frk1 = fork();
	if(id.frk1 < 0)
		ft_error("fork");
	else if (id.frk1 == 0)
		{
			while_mltpipes(id,envp);	
		}//end else
    if (waitpid(-1, NULL, 0) == -1)
		ft_error("waitpid");
	while(j<(id.argc - 4))
	{
		close(id.pii[j][0]);
		close(id.pii[j][1]);
		j++;
	}
    close(id.fd1);
	close(id.fd2);
}

void multpipes_chunk1(t_fds id, char *argv[], char *const envp[])
{
	int i;
	
	i = 0;
	id.fd1 = open(argv[1], O_RDWR | O_CREAT, 0666);
	id.fd2 = open(argv[id.argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
	//creation of the pipe:
	i = 0;
    while (i < (id.argc - 4))
    {
        if (pipe(id.pii[i]) == -1)
            ft_error("pipe");
		i++;
	}
	forking_mltpipes(id, envp);
}

//checks args and preparing cmds ana paths .
void	multiple_pipe(int argc, char *argv[], char *const envp[])
{
	int i;
    // int **pi; 
	// t_arg **prg;
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
	id.prg[i]= NULL;
	getting_paths_bns(envp, id.prg);
	concaten_pathscmd_bns(id.prg, argv);
	check_exist_cmdbns(id.prg);
	id.argc = argc;
	multpipes_chunk1(id, argv, envp);
	//END of preparing cmds and checks ERRORS !!!!
	// starting creating processes and creating pipes

}