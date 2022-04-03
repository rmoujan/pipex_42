/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:28 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/03 15:48:13 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int main(int argc, char *argv[], char *const envp[])
{
    int		id;
    int		i;
    char	**tab;
    checks_errors(argc);
    test_files(argv);
    //bringing the var PATH from envp :
    i = 0;
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
	    
    //printf("%s\n", envp[0]);
    id = fork();

    if (id < 0)
        perror("ERROR");
    //child process :
    else if (id == 0)
    {
        //should do here the first execeve function to execute the cmd1
         if (execve(argv[1], argv + 1, NULL) == -1)
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