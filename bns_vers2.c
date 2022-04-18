/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_vers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:51:52 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/18 23:16:52 by rmoujan          ###   ########.fr       */
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
	// pid_t *pid;
	pid_t frk;
    int **pi; 
	t_arg **prg;
	t_fds	id;
	
	i = 0;
	//checks errors and preparing cmds:
	checks_error_bns(argc);
	prg = (t_arg **)malloc(sizeof(t_arg *) * (argc - 3) + 1);
	// pid = (pid_t *)malloc (sizeof(pid_t) * (argc - 3));
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
		// printf("the pipe number %d\n", i);
		i++;
	}
	i = 0;
	//creation first process that read from file and execute cmd :
	// pid[i] = fork();
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
					printf("child process number %d \n",i);
                    if (i == 0)
                    {
                        printf("when i equal zero %d\n", i);
                        if (dup2(id.fd1, 0) == -1)
				        {
					        printf("first dup \n");
					        perror("dup2");
					        exit(1);
				        }
                        close(id.fd1);
                    }
                    else if (i != 0)
                    {
                        printf("when i not equal zero %d\n", i);
                        close(pi[i - 1][1]);
                        if (dup2(pi[i - 1][0], 0) == -1)
                        {
                            printf("first dup \n");
                            perror("dup2");
                            exit(1);
                        }
                    }
                    if (i == (argc - 4))
                    {
                        printf("when i equal %d\n", (argc - 4));
                        close(pi[i - 1][0]);
                        if (dup2(id.fd2, 1) == -1)
                        {
                            printf("second dup \n");
                            perror("dup2");
                            exit(1);
                        }
                    }
                    else if (i != (argc - 4))
                    {
                        printf("when i not equal (argc - 4) %d\n", i);
                        close(pi[i][0]);
                        if (dup2(pi[i][1], 1) == -1)
                        {
                            printf("second dup \n");
                            perror("dup2");
                            exit(1);
                        } 
                    }
                    fprintf(stderr,"********/la valeur de i est %d********/\n", i);
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
            printf("parent process \n");
			for (int j = 0; j < (argc - 4); j++)
			{
				close(pi[j][0]);
				close(pi[j][1]);
			}
            close(id.fd1);
			close(id.fd2);

	return (0);
}