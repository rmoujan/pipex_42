/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_vers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:51:52 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/19 13:38:39 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

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

int	main(int argc, char *argv[], char *const envp[])
{
	int i;
	pid_t frk;
    int **pi; 
	t_arg **prg;
	t_fds	id;
	
	i = 0;
	//checks errors and preparing cmds:
	checks_error_bns(argc);
	prg = (t_arg **)malloc(sizeof(t_arg *) * (argc - 3) + 1);
	pi = (int **) malloc(sizeof(int *) * (argc - 4));
	while (i < (argc - 4))
	{
		pi[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
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
	// starting creating processes and creating pipes
	id.fd1 = open(argv[1], O_RDWR | O_CREAT, 0666);
	id.fd2 = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
	// creation of the pipe:
	i = 0;
    while (i < (argc - 4))
    {
        if (pipe(pi[i]) == -1)
            ft_error("pipe");
		i++;
	}
	i = 0;
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
              for (int j = 0; j < (argc - 4); j++)
			    {
                    if (j != (i - 1))
                    {
                        close(pi[j][0]);
                    } 
                  
                    if (j != i)
                    {
                        close(pi[j][1]);
                    }   
                }
                    if (i == 0)
                    {
                        if (dup2(id.fd1, 0) == -1)
				        {
					        perror("dup2");
					        exit(1);
				        }
                        close(id.fd1);
                    }
                    else if (i != 0)
                    {
                        if (dup2(pi[i - 1][0], 0) == -1)
                        {
                            perror("dup2");
                            exit(1);
                        }
                    }
                    if (i == (argc - 4))
                    {
                        if (dup2(id.fd2, 1) == -1)
                        {
                            perror("dup2");
                            exit(1);
                        }
                    }
                    else if (i != (argc - 4))
                    {
                        if (dup2(pi[i][1], 1) == -1)
                        {
                            perror("dup2");
                            exit(1);
                        } 
                    }
					if (execve(prg[i]->path[0], prg[i]->cmd, envp) == -1)
					{
						perror("execve");
						exit(1);
					}
				}
				i++;
				}//end while
			
			}//end else
            waitpid(-1, NULL, 0);
			for (int j = 0; j < (argc - 4); j++)
			{
				close(pi[j][0]);
				close(pi[j][1]);
			}
            close(id.fd1);
			close(id.fd2);

	return (0);
}