/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup4_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:28 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/08 13:17:47 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	ft_exit(void)
{
	write(1, "ERROR\n", 6);
	exit(1);
}

//bring the cmd and her parameters from argv and 
//concatenate each path with "/commande" 
void	concaten_pathscmd(t_arg *prg, char *argv)
{
	int	i;

	i = 0;
	prg->cmd = ft_split(argv, ' ');
	while (prg->path[i])
	{
		prg->path[i] = ft_strjoin(prg->path[i], "/\0");
		prg->path[i] = ft_strjoin(prg->path[i], prg->cmd[0]);
		i++;
	}
}

void	getting_paths(char *const envp[], t_arg *prg)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			prg->path = ft_split(envp[i], ':');
			prg->path[0] = ft_strtrim(prg->path[0], "PATH=");
			break ;
		}
		i++;
	}
}

void	check_exist_cmd(t_arg *prg1)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (prg1->path[i])
	{
		if (access(prg1->path[i], F_OK) != -1)
		{
			prg1->path[0] = prg1->path[i];
			flag = 1;
		}
		i++;
	}
	// i = 0;
	// while (prg2->path[i])
	// {
	// 	if (access(prg2->path[i], F_OK) != -1)
	// 	{
	// 		prg2->path[0] = prg2->path[i];
	// 		flag = 1;
	// 	}
	// 	i++;
	// }
	if (flag == 0)
		ft_exit();
}

int main(int argc, char *argv[], char *const envp[])
{
    int		id;
    int		i;
    int		fd1;
    int		fd2;
    int		flag;
	int		pi[2];
	t_arg	*prg1;
	t_arg	*prg2;
	
    i = 0;
    flag = 0;
    checks_errors(argc);
    test_files(argv);
	//preparing first cmd
	prg1 =(t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg1);
	concaten_pathscmd(prg1, argv[2]);
    //preparing second cmd :
    prg2 =(t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg2);//WORKED
	concaten_pathscmd(prg2, argv[3]);
    check_exist_cmd(prg1); //just to minimize the code !!!
    check_exist_cmd(prg2);
	
	fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[4], O_RDWR);
	if (fd1 == -1 || fd2 == -1)
		ft_exit();
	
    if (pipe(pi) < 0)
        ft_exit();
	
    id = fork();
	i = 0;
    if (id < 0)
    {
        perror("fork");
        exit(1);
    }
    //child process :
    else if (id == 0)
    {
        //redirect the input to file
		if (dup2(fd1, 0) == -1)
        {
            perror("dup2");
            exit(1);
        }
		close(fd1);
        //for the pipe
        close(pi[0]);
        if (dup2(pi[1], 1) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(pi[1]);
        //should do here the first execeve function to execute the cmd1
        //checking is the command exits in some of the paths by using execeve :
        while (prg1->path[i])
        {
			flag = 0;
			//prg1->args[0] = prg1->path[i];
            if (execve(prg1->path[i], prg1->cmd, NULL) == -1)
                flag = 1;
            i++;
        }
		//if the command does not exists will appear this msg : 
		if (flag == 1)
		{
			perror("execve");
            exit(1);
		}
    }//END CHILD PROCESS
    
    //parent process :
    //pi[0]//read
    //pi[1]//write
    else
    {
        //will wait until the child process finish for bringing the data from child process!!
        //should do here the second execeve function to execute the cmd2
        wait(NULL);
        close(pi[1]);
        //redirect the pipe to input for the cmd2
		if (dup2(pi[0], 0) == -1)
        {
            perror("dup2");
            exit(1);
        }
		close(pi[0]);
        //rdirect the output to file
        if (dup2(fd2, 1) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(fd2);
        while (prg2->path[i])
        {
			flag = 0;
            if (execve(prg2->path[i], prg2->cmd, NULL) == -1)
                flag = 1;
         i++;
        }
		//if the command does not exists will appear this msg : 
		if (flag == 1)
		{
			perror("execve");
            exit(1);
		}
        // printf("****** PARENT PROCESS ******\n");

    // while (1)
    // {
        
    // }
    }
// printf("after parent process \n");
    return (0);
}
