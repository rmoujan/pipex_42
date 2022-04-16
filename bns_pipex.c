/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:20:25 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/16 12:31:53 by rmoujan          ###   ########.fr       */
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
	int pid[argc - 3];
    int pi[argc - 4][2]; 
	t_arg **prg;
	t_fds	id;
	
	i = 0;
	//checks errors and preparing cmds:
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
	// //
	// int j = 0;
	// i = 0;
	// while (prg[j])
	// {
	// 	i = 0;
	// 	while (prg[j]->path[i])
	// 	{
	// 		printf("prg[%d]->cmd[%d] == %s\n",j,i, prg[j]->path[i]);
	// 		i++;
	// 	}
	// 	printf("*********\n");
	// j++;
	// }
	// //
	
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
		printf("the process number %d \n", i);
		i++;
	}
	// i = 0;
	// // working with processes :
	// //wait for all the child processes to finish executing :
	while (wait(NULL) != -1);
	// while (i < (argc - 3))
	// 	wait(NULL);
	// i = 0;
	// while (i < 4)
	// {
	// 	printf("pid[%d] == %d\n", i, pid[i]);
	// 	i++;
	// }	
	// //END checking and creating processes and creating pipes
	id.fd1 = open(argv[1], O_RDWR | O_CREAT, 0666);
	id.fd2 = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
	//starting forking ::
	i = 0;
	while (i < (argc - 3 ))
	{
		if (pid[i] == 0)
		{
			//should here execute the childs processes !!!
			printf("child process number %d \n", i);
	if (dup2(id.fd1, 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(id.fd1);
	close(id.pi[0]);
	ft_close(id, pi, i, argc);
	if (dup2(id.pi[1], 1) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(id.pi[1]);
	if (execve(prg[i]->path[0], prg[i]->cmd, envp) == -1)
	{
		perror("execve");
		exit(1);
	}
			
		}
		// else
		// {
		// 	printf("parent process number %d\n", i);
		// }
		i++;
	}

	// END 
	
	// for(int i=0;i<argc - 3;i++) // loop will run n times (n=5)
    // {
    //     if(fork() == 0)
    //     {
    //         printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
    //         exit(0);
    //     }
    // }
    // for(int i=0;i<3;i++) // loop will run n times (n=5)
    // wait(NULL);
	// //starting forking:
	// i = 0;
	// pid[i] = fork();
	
	// if (pid[i++] == 0)
	// {
	// 	//first child process 
	// }
	// else {
	// 	while (i < (argc - 4))
	// 	{
	// 		pid[i] = fork();
	// 		if (pid[i++] == 0)
	// 		{
	// 			//second child :
	// 		}
	// 		else
	// 		{
					
	// 		}
	// 	}
	// }
	// i = 0;
	// while (i < (argc - 3))
	// {
	// 	pid[i] = fork(); 
	// 	if (pid[i] < 0)
	// 		ft_error("fork");
	// 	else if (pid[i] == 0)
	// 	{
	// 		//first process
	// 		printf("first process number %d\n", i);
	// 	}
	// 	i++;
	// }
	
	// i = 0;
	// while (i < (argc - 3))
	// {
	// 	if (pid[i] == 0)
	// 	{
	// 		//first process
	// 		printf("first process number %d\n", i);
	// 	}
	// 	// else
	// 	// {
	// 	// 	waitpid(pid[i], NULL, 0);
	// 	// 	printf("parent process \n");
	// 	// }
	// i++;
	// }
	
	// i = 0;
	// pid = fork();
	// if (pid < 0)
	// 	 ft_error("fork");
	// else if (pid == 0)
	// {
	// 	//first child process :
	// 	printf("first child process \n");
	// }
	// else
	// {
	// 	//parent process :
	// 	while (i < (argc - 5))
	// 	{
	// 		pid2[i] = fork();
	// 		if (pid2[i] < 0)
	// 			ft_error("fork");
	// 		if (pid2[i] == 0)
	// 		{
	// 			printf("process number %d\n", i);		
	// 		}
	// 		i++;
	// 	}
	// }
	
	return (0);
}