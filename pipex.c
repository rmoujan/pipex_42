/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:28 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/04 12:40:18 by rmoujan          ###   ########.fr       */
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
void	allocate_frstexec(char **argv, t_cmd cmd1)
{
	cmd1.name = ft_split(argv[2], ' ');
	cmd1.lines = 0;
	while (cmd1.name[cmd1.lines])
		cmd1.lines++;
}

int main(int argc, char *argv[], char *const envp[])
{
    int		id;
    int		i;
    int		flag;
	int		size;
    char	**tab;
	char	*file;
	t_cmd	cmd1;
	char	**args1;
	
    checks_errors(argc);
    test_files(argv);
    //bringing the var PATH from envp :
    i = 0;
    flag = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH", 4) == 0)
        {
            tab = ft_split(envp[i], ':');
            tab[0] =ft_strtrim(tab[0], "PATH=");
            break;
        }
        i++;
    }
    //fill the cmd1 with the path ,cmd and his parameters , and file1 :
	//first of all must calcul how many args we have , for allocating the tab cmd1:
	cmd1.name = allocate_frstexec(argv);
	args1 = (char *) malloc(sizeof(char *) * (size + 1));
	
    id = fork();
	i = 0;
    if (id < 0)
        perror("ERROR");
    //child process :
    else if (id == 0)
    {
        //should do here the first execeve function to execute the cmd1
        //checking is the command exits in some of tha paths by using execeve :
        while (tab[i])
        {
            if (execve(tab[i], args1, envp) == -1)
                flag = 1;
            i++;
        }
		//if the command does not exists will appear this msg : 
		if (flag == 1)
			perror("execve");
    }
    //parent process :
    else
    {
        //will wait until the child process finish for bringing the data from child process!!
        //should do here the second execeve function to execute the cmd2
        wait(NULL);
        printf("*****\n");
    }
    return (0);
}