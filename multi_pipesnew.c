/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipesnew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 01:20:24 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/21 01:48:57 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"

void chunks_multpipes(int argc, char *argv[], char *const envp[], t_arg **prg)
{
    int i;
	int j;
	t_fds	id;
    int **pi;

	i = 0;
	pi = (int **) malloc(sizeof(int *) * (argc - 4));
	while (i < (argc - 4))
	{
		pi[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}

	id.fd1 = open(argv[1], O_RDWR | O_CREAT, 0666);
	id.fd2 = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
	//creation of the pipe:
	i = 0;
    while (i < (argc - 4))
    {
        if (pipe(pi[i]) == -1)
            ft_error("pipe");
		i++;
	}
	i = 0;
    

	

	// starting multiple pipes !!!!
	//when the input is not the heredoc !!!
	//creation first process that read from file and execute cmd :
	frk = fork();
	if(frk < 0)
		ft_error("fork");
	else if (frk == 0)
		{

			while (i < (argc - 3))
			{
				frk = fork();
				if(frk < 0)
					ft_error("fork");
				else if (frk  == 0)
				{
				   while (j < (argc - 4))
					{
						if (j != (i - 1))
							close(pi[j][0]);
					
						if (j != i)
							close(pi[j][1]);
						j++;
					}
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
				i++;
			}//end while
			
			}//end else
			
            if (waitpid(-1, NULL, 0) == -1)
				ft_error("waitpid");
			for (int j = 0; j < (argc - 4); j++)
			{
				close(pi[j][0]);
				close(pi[j][1]);
			}
            close(id.fd1);
			close(id.fd2);

}

void multiple_pipe(int argc, char *argv[], char *const envp[], t_arg **prg)
{
    
	int i;
	t_arg **prg;
	// t_fds	id;

    	
	checks_errormltpipe(argc);
	prg = (t_arg **)malloc(sizeof(t_arg *) * (argc - 3) + 1);
	i = 0;
	while (i < (argc - 3))
	{
		prg[i] = (t_arg *)malloc(sizeof(t_arg));
		i++;
	}
	prg[i]= NULL;
	getting_paths_bns(envp, prg);
	concaten_pathscmd_bns(prg, argv);
	check_exist_cmdbns(prg);
	//END of preparing cmds and checks ERRORS !!!!
	//starting creating processes and creating pipes
    chunks_multpipes(argc, argv, envp, prg);
}