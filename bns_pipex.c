/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:20:25 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/14 17:48:17 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//handle multiple pipes :
void	ft_error(char *str)
{
	perror(str);
	exit(1);
}

int	main(int argc, char *argv[], char *const envp[])
{
	int i;
	checks_error_bns(argc);
	int pid[argc - 3];
    int fd[argc - 4][2];
	t_arg **prg;
	
	i = 0;
	//checks errors and preparing cmds:
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
	//
	int j = 0;
	i = 0;
	while (prg[j])
	{
		i = 0;
		while (prg[j]->path[i])
		{
			printf("prg[%d]->path[%d] == %s",j,i, prg[j]->path[i]);
			i++;
		}
	j++;
	}

	
	// //creation of the pipe:
    // while (i < (argc - 4))
    // {
    //     if (pipe(fd[i]) == -1)
    //         ft_error("pipe");
	// 	//printf("the pipe number %d\n", i);
	// 	i++;
	// }
	// i = 0;
	// //creation processes :
	// while (i < (argc - 3))
	// {
	// 	pid[i] = fork();
	// 	if(pid[i] < 0)
	// 		ft_error("fork");
	// 	else if (pid[i] == 0)
	// 		return (0);
	// 	// printf("the process number %d \n", i);
	// 	i++;
	// }
	// i = 0;
	// // working with processes :
	
	// //wait for all the child processes to finish executing :
	// // while (wait(NULL) != -1);
	// while (i < (argc - 3))
	// 	wait(NULL);
	
	// //END



	
	// i = 0;
	// while (i < (argc - 3 ))
	// {
	// 	//beginnen :
	// 	if (pid[i] == 0)
	// 	{
	// 		printf("child process number %d \n", i);
	// 	}
	// 	else
	// 	{int j = 0;
			
	// 		while (j < (argc - 3))
	// 		{
	// 		waitpid(pid[j],NULL, 0);
	// 		printf("parent process number %d\n", j);
	// 		j++;
	// 		}

	// 	}
	// 	i++;
	// }
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