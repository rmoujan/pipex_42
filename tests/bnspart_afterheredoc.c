/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bnspart_afterheredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 01:40:54 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/20 01:40:57 by rmoujan          ###   ########.fr       */
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
/*   Updated: 2022/04/20 01:40:17 by rmoujan          ###   ########.fr       */
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

int	main(int argc, char *argv[], char *const envp[])
{
	int i;
	int j;
	// pid_t frk;
    int **pi; 
	t_arg **prg;
	t_fds	id;
	char *str;
	t_fds idoc;
	int pidoc[2][2];
	int k;

	i = 0;
	j = 0;
	k = 0;
	//checks errors and preparing cmds:
	//should the main divide in two programmes : multiple pipes and heredoc :
	//starting heredoc :::
	ft_heredoc(argc, argv, envp);
	
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
	//creation of the pipe:
	i = 0;
    while (i < (argc - 4))
    {
        if (pipe(pi[i]) == -1)
            ft_error("pipe");
		i++;
	}
	i = 0;
	//when the input is from HEREDOC :
	if (ft_strcmp(argv[1], "here_doc\0") == 0)
	{
		if (pipe(pidoc[0]) == -1)
			ft_error("pipe");
		
		write(0,"heredoc>", 8);
		str = get_next_line(0);
		str = ft_strtrim(str, "\n");
		while (strcmp(str, argv[2]) != 0)
		{
			str = ft_strjoin(str, "\n");
			write(0,"heredoc>", 8);
			write(pidoc[0][1], str, ft_strlen(str));
			free(str);
			str = get_next_line(0);
			str = ft_strtrim(str, "\n");
		}
		close(pidoc[0][1]);
		//starting forking :
		idoc.frk1 = fork();
		if (idoc.frk1 < 0)
			ft_error("fork");
		else if (idoc.frk1 == 0)
		{
				//CHild process :
				if (dup2(pidoc[0][0], 0) == -1)
					ft_error("dup2");
				close(pidoc[0][0]);
				close(pidoc[1][0]);
				if (dup2(pidoc[1][1], 1) == -1)
				{
					perror("dup2");
					exit(1);
				}
				close(pidoc[1][1]);
				if (execve(prg1->path[0], prg1->cmd, envp) == -1)
				{
					perror("execve");
					exit(1);
				}
		}
		else
		{
				//PARENT PROCESS :
				id.frk2 = fork();
				if (id.frk2 < 0)
				{
					perror("fork");
					exit(1);
				}
				else if (id.frk2 == 0)
				{
					close(pidoc[1][1]);
					if (dup2(pidoc[1][0], 0) == -1)
					{
						perror("dup2");
						exit(1);
					}
					close(pidoc[1][0]);
					if (dup2(id.fd2, 1) == -1)
					{
						perror("dup2");
						exit(1);
					}
					close(id.fd2);
					if (execve(prg2->path[0], prg2->cmd, envp) == -1)
					{
						perror("execve");
						exit(1);
					}
				}
				else
				{
						while (k < 2)
						{
							close(pidoc[k][1]);
							close(pidoc[k][0]);
							k++;
						}
						close(id.fd1);
						close(id.fd2);
						if (waitpid(id.frk1, NULL, 0) == -1)
							perror("waitpid");
						if (waitpid(id.frk2, NULL, 0) == -1)
							perror("waitpid");
				}
		}
		
		// printf("*** output the data from the pipe[0][0] ***\n");
		// // read((pidoc[0][0]), str, 1000);
		// str = get_next_line(pidoc[0][0]);
		// 	// printf("error \n");
		// printf("the str is == %s\n", str);
		// while (str)
		// {
		// 	printf("|%s|\n", str);
		// 	str = get_next_line(pidoc[0][0]);
		// }
		
		printf("inside heredoc \n");
	}
	
	//when the input is not the heredoc !!!
	//creation first process that read from file and execute cmd :
	// else
	// {
	// frk = fork();
	// if(frk < 0)
	// 	ft_error("fork");
	// else if (frk == 0)
	// 	{

	// 		while (i < (argc - 3))
	// 		{
	// 			frk = fork();
	// 			if(frk < 0)
	// 				ft_error("fork");
	// 			else if (frk  == 0)
	// 			{
	// 			   while (j < (argc - 4))
	// 				{
	// 					if (j != (i - 1))
	// 						close(pi[j][0]);
					
	// 					if (j != i)
	// 						close(pi[j][1]);
	// 					j++;
	// 				}
    //                 if (i == 0)
    //                 {
    //                     if (dup2(id.fd1, 0) == -1)
	// 						ft_error("dup2");
    //                     close(id.fd1);
    //                 }
    //                 else if (i != 0)
    //                 {
    //                     if (dup2(pi[i - 1][0], 0) == -1)
    //                         ft_error("dup2");
    //                 }
    //                 if (i == (argc - 4))
    //                 {
    //                     if (dup2(id.fd2, 1) == -1)
    //                         ft_error("dup2");
    //                 }
    //                 else if (i != (argc - 4))
    //                 {
    //                     if (dup2(pi[i][1], 1) == -1)
    //                         ft_error("dup2");
    //                 }
	// 				if (execve(prg[i]->path[0], prg[i]->cmd, envp) == -1)
	// 					ft_error("execve");
	// 			}
	// 			i++;
	// 		}//end while
			
	// 		}//end else
			
    //         if (waitpid(-1, NULL, 0) == -1)
	// 			ft_error("waitpid");
	// 		for (int j = 0; j < (argc - 4); j++)
	// 		{
	// 			close(pi[j][0]);
	// 			close(pi[j][1]);
	// 		}
    //         close(id.fd1);
	// 		close(id.fd2);
	// }
	
	return (0);
}