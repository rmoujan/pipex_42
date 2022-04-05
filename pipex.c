/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:28 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/05 16:46:10 by rmoujan          ###   ########.fr       */
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

//calcul how many lines we have in args for the first exceve
// ./pipex infile "ls -l" "wc -l" outfile
void	cmd_parameters(char **argv, t_cmd *cmd1)
{
	cmd1->name = ft_split(argv[2], ' ');
	cmd1->lines = 0;
	while (cmd1->name[cmd1->lines])
		cmd1->lines++;
}

void ft_exit()
{
	write(1, "ERROR\n", 6);
	exit(1);
}

//fill the args with the cmd and her parameters !!!
void creating_args(char ***args, t_cmd cmd1)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (cmd1.name[j])
	{
		(*args)[i] = cmd1.name[j];
		i++;
		j++;
	}
	(*args)[i] = NULL;
}

//should concatene each path with  "/commande" 
char **concat_pathwithcmd(char **path, t_cmd cmd1)
{
	int i;

	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/\0");
		path[i] = ft_strjoin(path[i], cmd1.name[0]);
		i++;
	}
	return (path);
}

// void	getting_paths(char **envp, t_arg *prg)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
//     {
//         if (ft_strncmp(envp[i], "PATH", 4) == 0)
//         {
//             prg->path = ft_split(envp[i], ':');
//             prg->path[0] = ft_strtrim(prg->path[0], "PATH=");
//             break;
//         }
//         i++;
//     }
// }

int main(int argc, char *argv[], char *const envp[])
{
    int		id;
    int		i;
    int		flag;
	int		size;
    char	**path = NULL;
	t_cmd	cmd1;
	char	**args1;
	//int		f[2];
	//t_arg	prg1;
	//t_arg	prg2;
	
   checks_errors(argc);
    test_files(argv);
    //bringing the var PATH from envp :
    i = 0;
    flag = 0;
	//this part is worked well
    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], "PATH", 4) == 0)
        {
            path = ft_split(envp[i], ':');
            path[0] = ft_strtrim(path[0], "PATH=");
            break;
        }
        i++;
    }
	//later :: 
	//prg1 = malloc(sizeof(t_arg));
	//getting_paths(envp, &prg1);
	
    // //fill the cmd1 with the path ,cmd and his parameters :
	// //first of all must calcul how many args we have , for allocating the tab cmd1:
	cmd_parameters(argv, &cmd1);
	size = cmd1.lines + 2;
	args1 = (char **) malloc(sizeof(char *) * (size));
	if (args1 == NULL)
		ft_exit();
	creating_args(&args1, cmd1);
	path = concat_pathwithcmd(path, cmd1);
		
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit();
	//int fd = file_into_str(argv[1]);
    id = fork();
	i = 0;
    if (id < 0)
        perror("ERROR");
    //child process :
    else if (id == 0)
    {
        //should do here the first execeve function to execute the cmd1
        //checking is the command exits in some of the paths by using execeve :
		if (dup2(fd, 0) == -1)
			perror("dup2");
		close(fd);
        while (path[i])
        {
			flag = 0;
			args1[0] = path[i];
            if (execve(path[i], args1 + 1, NULL) == -1)
                flag = 1;
            i++;
        }
		//if the command does not exists will appear this msg : 
		if (flag == 1)
		{
			printf("==============");
			perror("execve");
			printf("insid if when execve failed !!!!! \n");
		}
    }
    //parent process :
    else
    {
        //will wait until the child process finish for bringing the data from child process!!
        //should do here the second execeve function to execute the cmd2
        wait(NULL);
        printf("****** PARENT PROCESS ******\n");
    }
	
    return (0);
}