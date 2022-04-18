/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_bnspipex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:14:44 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/16 15:14:46 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:20:25 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/16 15:13:29 by rmoujan          ###   ########.fr       */
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
	//
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
	// 	break;
	// 	printf("*********\n");
	// j++;
	// }
	//
		// //END checking and creating processes and creating pipes
	id.fd1 = open(argv[1], O_RDWR | O_CREAT, 0666);
	id.fd2 = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
	// //creation of the pipe:
    while (i < (argc - 4))
    {
        if (pipe(pi[i]) == -1)
            ft_error("pipe");
		//printf("the pipe number %d\n", i);
		i++;
	}
	i = 0;
	//creation processes :
	while (i < (argc - 3))
	{
		pid[i] = fork();
		if(pid[i] < 0)
			ft_error("fork");
		else if (pid[i] == 0)
			return (0);
		//printf("the process number %d \n", i);
		i++;
	}
	// i = 0;
	// // working with processes :
	// //wait for all the child processes to finish executing :
	while (wait(NULL) != -1);
	// while (i < (argc - 3))
		//wait(NULL);
	

	//starting forking ::
	i = 0;
	while (i < (argc - 3 ))
	{
		if (i == 0)
		{
			// printf("koko \n");
			//should here execute the first process that read from file
			if (pid[i] == 0)
			{
				printf("inside first process \n");
				if (dup2(id.fd1, 0) == -1)
				{
					perror("dup2");
					exit(1);
				}
				// close(id.fd1);
				// close(id.pi[0]);
				ft_close_all(id, i, argc, pi);
				if (dup2(pi[0][1], 1) == -1)
				{
					perror("dup2");
					exit(1);
				}
				close(pi[0][1]);
				if (execve(prg[0]->path[0], prg[0]->cmd, envp) == -1)
				{
					perror("execve");
					exit(1);
				}
			}
			else
			{
				printf("else \n");
			}
		}
		
		else if (i == (argc - 4))
		{
			// waitpid(pid[0], NULL,0);
			////should here execute the last process that write into file
			printf("last process \n");
		}

		else
		{
			// waitpid(pid[0], NULL,0);
			//execute the others process(pipes) :
			printf("inter processes \n");	
		}
		
		i++;
	}
	
	
	return (0);
}