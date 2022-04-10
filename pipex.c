/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:28 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/10 13:28:02 by rmoujan          ###   ########.fr       */
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

// void    f_free(t_arg **prg)
// {
//     int i;
//     t_arg *arg;

//     i = 0;
//     arg = *prg;
//     while (arg->path[i])
//     {
//         free(arg->path[i]);
//         i++;
//     }
//     free(arg->path);
// }

// void	check_cmd(t_arg prg)
// {
	
// }
int main(int argc, char *argv[], char *const envp[])
{
    t_fds   id;
	t_arg	*prg1;
	t_arg	*prg2;
    int status;
    
    checks_errors(argc);
    test_files(argv);
	//preparing first cmd :
	prg1 =(t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg1);
	concaten_pathscmd(prg1, argv[2]);
    //preparing second cmd :
    prg2 =(t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg2);//WORKED
	concaten_pathscmd(prg2, argv[3]);
    check_exist_cmd(prg1, prg2); //just to minimize the code !!!
    //check_exist_cmd(prg2);
	
	id.fd1 = open(argv[1], O_RDONLY);
    id.fd2 = open(argv[4], O_RDWR);
    
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
    if (pipe(id.pi) < 0)
        ft_exit();
    id.frk1 = fork();
    if (id.frk1 < 0)
    {
        perror("fork");
        exit(1);
    }
    //child process :
    else if (id.frk1 == 0)
    {
        //redirect the input to file .. that makes execve read from the file for execute the cmd
        //donk ay haja te7t had cmd raah aywli yakhud input from file(fd1)
       // pid1 = getpid();
       printf("child 1 \n");
		if (dup2(id.fd1, 0) == -1)
        {
            perror("dup2");
            exit(1);
        }
		close(id.fd1);
        //for the pipe
        close(id.pi[0]);
        //result li atjini mn exceve ankhzenha f pi[1]
        if (dup2(id.pi[1], 1) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(id.pi[1]);
        //should do here the first execeve function to execute the cmd1
        if (execve(prg1->path[0], prg1->cmd, envp) == -1)
		{
			perror("execve");
			exit(1);
		}
    }//END CHILD PROCESS
    else
    {
        //will wait until the child process finish for bringing the data from child process!!
        //should do here the second execeve function to execute the cmd2
        // waitpid(id.frk1, &status, 0);
        id.frk2 = fork();
        if (id.frk2 < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (id.frk2 == 0)
        {
            waitpid(id.frk1, &status, 0);
            // wait(NULL);
            //pid2 = getpid();
            printf("childd 2\n");
            close(id.pi[1]);
            //redirect the pipe to input for the cmd2
            if (dup2(id.pi[0], 0) == -1)
            {
                perror("dup2");
                exit(1);
            }
            close(id.pi[0]);
            //rdirect the output to file
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
           // waitpid(id.frk1, &status, 0);
          //  waitpid(id.frk2, &status, 0);
            wait(NULL);
            printf("parent process \n");
            // f_free(&prg1);

    // int i;
    // // //t_arg *arg;

    // i = 0;
    // // //arg = *prg;
    // while (prg1->path[i])
    // {
    //     free(prg1->path[i]);
    //     i++;
    // }
    // free(prg1->path[i]);
    // while (1)
    //     {
                    
    //     }
    //should do here free !!!!!
    }
    }
    // wait(NULL);
    // if (id.frk1 != 0 && id.frk2 != 0)
    // {
    //     //must free leaks here !!!!
    //     printf("finally inside parent process \n");
    // }

    return (0);
}
    //parent process :
    //pi[0]//read
    //pi[1]//write