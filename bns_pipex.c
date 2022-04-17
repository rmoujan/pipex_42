/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:20:25 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/17 13:11:35 by rmoujan          ###   ########.fr       */
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
	pid_t *pid;
    int **pi; 
	t_arg **prg;
	t_fds	id;
	
	i = 0;
	//checks errors and preparing cmds:
	checks_error_bns(argc);
	prg = (t_arg **)malloc(sizeof(t_arg *) * (argc - 3) + 1);
	pid = (pid_t *)malloc (sizeof(pid_t) * (argc - 3));
	pi = (int **) malloc(sizeof(int *) * (argc - 4));
	while (i < (argc -4 ))
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
	// int j = 0;
	// i = 0;
	// while (prg[j])
	// {
	// 	i = 0;
	// 	while (prg[j]->cmd[i])
	// 	{
	// 		printf("prg[%d]->cmd[%d] == %s\n",j,i, prg[j]->cmd[i]);
	// 		i++;
	// 	}
	// 	// break;
	// 	printf("*********\n");
	// j++;
	// }
	// //**
	// j = 0;
	// i = 0;
	// while (prg[j])
	// {
	// 	i = 0;
	// 	while (prg[j]->path[i])
	// 	{
	// 		printf("prg[%d]->cmd[%d] == %s\n",j,i, prg[j]->path[i]);
	// 		i++;
	// 	}
	// 	// break;
	// 	printf("*********\n");
	// j++;
	// }
	//**
	// starting creating processes and creating pipes
	id.fd1 = open(argv[1], O_RDWR | O_CREAT, 0666);
	id.fd2 = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
	// //creation of the pipe:
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
	pid[i] = fork();
	if(pid[i] < 0)
			ft_error("fork");
		else if (pid[i] == 0)
		{
				// printf("koko \n");
				//should here execute the first process that read from file
				printf("inside first process and i == %d\n", i);
				if (dup2(id.fd1, 0) == -1)
				{
					printf("first dup \n");
					perror("dup2");
					exit(1);
				}
				ft_close_all(id, i, argc, pi);
				if (dup2(pi[0][1], 1) == -1)
				{
					printf("second dup \n");
					perror("dup2");
					exit(1);
				}
				i++;
				write(pi[0][1], &i, sizeof(int));
				close(pi[0][1]);
				if (execve(prg[0]->path[0], prg[0]->cmd, envp) == -1)
				{
					perror("execve");
					exit(1);
				}
		}
		else
		{
			//parent process :
			wait(NULL);
			// printf("une seule fois \n");
			// read(pi[0][0], &i, sizeof(x));
			printf("\n from parent process i is == %d \n", i);
			//had while hiya li 3eliha kolshiii !!!!!!
			i++;
			while (i <= (argc - 5))
			{
				printf("inside while \n");
				// read(pi[i - 1][0], &i, sizeof(x));
				pid[i] = fork();
				if(pid[i] < 0)
					ft_error("fork");
				else if (pid[i]  == 0)
				{
					printf("child process number %d \n",i);
					//child process :
					ft_close_all(id, i, argc, pi);
					close(pi[i - 1][1]);
					if (dup2(pi[i - 1][0], 0) == -1)
					{
						printf("first dup \n");
						perror("dup2");
						exit(1);
					}
					close(pi[i - 1][0]);
					if (dup2(pi[i][1], 1) == -1)
					{
						printf("second dup \n");
						perror("dup2");
						exit(1);
					}
					// i++;
					// write(pi[i][1], &i, sizeof(int));
					close(pi[i][1]);
					if (execve(prg[i]->path[0], prg[i]->cmd, envp) == -1)
					{
						perror("execve");
						exit(1);
					}
				}
				printf("\n after execev \n");
				i++;
			}
			if (pid[i] != 0)
				{
					wait(NULL);
					//parent process:
					//should do the last process when cmd send the output to file:
					printf("parent process \n");
						
				}
		}
		return (0);
}