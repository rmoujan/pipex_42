/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:20:25 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/19 17:34:57 by rmoujan          ###   ########.fr       */
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
	pid_t frk;
    int **pi; 
	t_arg **prg;
	t_fds	id;
	char *str;
	
	i = 0;
	j = 0;
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
	if (ft_strcmp(argv[1], "here_doc\0") != 0)
		id.fd1 = open(argv[1], O_RDWR | O_CREAT, 0666);
	if (ft_strcmp(argv[1], "here_doc\0") != 0)
		id.fd2 = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	else
		id.fd2 = open(argv[argc - 1], O_RDWR | O_APPEND | O_CREAT, 0666);
	
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
		str = get_next_line(0);
		while (strcmp(str, argv[2]) == 0)
		{
			printf("%s \n", str);
			str = get_next_line(0);
		}
		
		printf("insid herdoc \n");
	}
	//when the input is not the heredoc !!!
	//creation first process that read from file and execute cmd :
	else
	{
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
	
	return (0);
}