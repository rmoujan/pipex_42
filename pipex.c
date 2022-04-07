/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:28 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/07 12:10:37 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void checks_errors(int argc)
{
    if (argc != 5)
    {
        write(1, "ERROR MANAGEMENT \n", 18);
        exit(1);
    }
}        

void test_files(char *argv[])
{
    if (access(argv[1], F_OK) == -1 || access(argv[1], R_OK | W_OK | X_OK) == -1)
    {
        write(1, "ERROR OCCURED WHEN CHECKING FILES \n", 35);
        exit(1);
    }
     if (access(argv[4], F_OK) == -1 || access(argv[4], R_OK | W_OK | X_OK) == -1)
    {
        write(1, "ERROR OCCURED WHEN CHECKING FILES \n", 35);
        exit(1);
    }
    // else
    // {
    //     printf("there is no error \n");
    // }
    // int test, test2;
    // test = access(argv[1], F_OK);
    // printf("test == %d\n", test);
    // test2 = access(argv[1], R_OK | W_OK | X_OK);
    // printf("tes2 == %d\n", test2);
}

//bring the cmd and his parameters  :
//must calcul the numbers of cmd and his parameters (to allocate the tab cmd):
void	cmd_parameters(char **argv, t_arg *prg)
{
	prg->cmd.name = ft_split(argv[3], ' ');
	prg->cmd.lines = 0;
	while (prg->cmd.name[prg->cmd.lines])
		prg->cmd.lines++;
}

void ft_exit()
{
	write(1, "ERROR\n", 6);
	exit(1);
}

//fill the args with the cmd and her parameters !!!
void creating_args(t_arg *prg)
{
	int i;
	int j;

	i = 1;
	j = 0;
    //prg->args[0] = "/usr/bin";
	while (prg->cmd.name[j])
	{
        prg->args[i] = prg->cmd.name[j];
		i++;
		j++;
	}
    prg->args[i] = NULL;
}

//should concatene each path with  "/commande" 
void concat_pathwithcmd(t_arg *prg)
{
	int i;

	i = 0;
	while (prg->path[i])
	{
		prg->path[i] = ft_strjoin(prg->path[i], "/\0");
		prg->path[i] = ft_strjoin(prg->path[i], prg->cmd.name[0]);
		i++;
	}
	//return (prg->path[i]);
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
            break;
        }
        i++;
    }
}

int main(int argc, char *argv[], char *const envp[])
{
    int		id;
    int		i;
    int		flag;
	int		pi[2];
	t_arg	*prg1;
	t_arg	*prg2;
	
    //checks_errors(argc);
    //test_files(argv);
    i = 0;
    flag = 0;
	prg1 =(t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg1);//WORKED
	cmd_parameters(argv, prg1);
	prg1->args = (char **) malloc(sizeof(char *) * (prg1->cmd.lines + 2));
	if (prg1->args == NULL)
		ft_exit();
	creating_args(prg1);
	concat_pathwithcmd(prg1);
    //preparing the 2 cmd :
    prg2 =(t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg2);//WORKED
	cmd_parameters(argv, prg2);
	prg2->args = (char **) malloc(sizeof(char *) * (prg2->cmd.lines + 2));
	if (prg2->args == NULL)
		ft_exit();
	creating_args(prg2);
	concat_pathwithcmd(prg2);
        
	int fd = open(argv[1], O_RDONLY);
    int fd2 = open(argv[4], O_RDWR);
	if (fd == -1)
		ft_exit();
    if (pipe(pi) < 0)
        exit(1);
    id = fork();
	i = 0;
    if (id < 0)
        perror("ERROR");
    //child process :
    else if (id == 0)
    {
        //redirect the input to file
		if (dup2(fd, 0) == -1)
			perror("dup2");
		close(fd);
        //for the pipe
        close(pi[0]);
        if (dup2(pi[1], 1) == -1)
            perror("dup2");
        close(pi[1]);
        //should do here the first execeve function to execute the cmd1
        //checking is the command exits in some of the paths by using execeve :
        while (prg1->path[i])
        {
			flag = 0;
			prg1->args[0] = prg1->path[i];
            if (execve(prg1->path[i], prg1->args + 1, NULL) == -1)
                flag = 1;
            i++;
        }
		//if the command does not exists will appear this msg : 
		if (flag == 1)
		{
			perror("execve");
            ft_exit();
		}
    }
    //parent process :
    else
    {
        //will wait until the child process finish for bringing the data from child process!!
        //should do here the second execeve function to execute the cmd2
        wait(NULL);
        close(pi[1]);
        //redirect the THE pipe to input
		if (dup2(pi[0], 0) == -1)
			perror("dup2");
		close(pi[0]);
        close(pi[1]);
        //rdirect the output to file
        if (dup2(fd2, 1) == -1)
        {
            printf("error");
            perror("dup2");
        }
        //close(fd2);
        while (prg2->path[i])
        {
			flag = 0;
			prg2->args[0] = prg2->path[i];
            if (execve(prg2->path[i], prg2->args + 1, NULL) == -1)
                flag = 1;
            i++;
        }
		//if the command does not exists will appear this msg : 
		if (flag == 1)
		{
			perror("execve");
            ft_exit();
		}
        printf("****** PARENT PROCESS ******\n");
    }
	
    return (0);
}