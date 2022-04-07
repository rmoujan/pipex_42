/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup2_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:28 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/05 12:19:47 by rmoujan          ###   ########.fr       */
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


//creating the args for the first exceve():
//I think you don't bash t7sbi lhadshi kaml 7e9ash you are already using split
//st split deja kat clacule l each str
// void	allocating_space(char ***args, char **path, char **argv, t_cmd	cmd1)
// {
// 	// int	i;
// 	// int j;

// 	// i = 1;
// 	// j = 0;
// 	//let the path ankhdem 3liha bu7dha !!!
// 	//in this whill .. I'll work just on cmd and his parameters :
// 	// while (cmd1.name[j])
// 	// {
// 	// 	args[i] = (char *) malloc(sizeof(char) * (ft_strlen(cmd1.name[i]) + 1));
// 	// 	i++;
// 	// 	j++;
// 	// }
// 	//still the file :
	
// }
//mashi b darora t recivi pointer as double pointer .. fash dert visualisation l9it
// ghi be single pointer n9der nbdlo (do *file bash t accedi lvalue of pointer)
void	file_into_str(char *argv, char **file)
{
	int		fd;
	char	*str;

	fd = open(argv, O_RDWR);

	str = get_next_line(fd);
	while (str)
	{
		*file = ft_strjoin(*file, str);
		//free(str);
		//free(file);
		str = get_next_line(fd);
	}
}
//must cheak it again hiya li fiha lmoshkiiiil !!!!!
void creating_args(char ***args, char *file, t_cmd cmd1, int size)
{
	int i;
	int j;

	i = 1;
	j = 0;
	//*tab)[i]
//	(*args)[0] = "/bin/src";//just an example
	while (cmd1.name[j])
	{
		(*args)[i] = cmd1.name[j];
		i++;
		j++;
	}
	(*args)[i] = file;
	i++;
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
	//path[i] = ft_strjoin(path[i], "/\0");
	i++;
	}
	return (path);
}

int main(int argc, char *argv[], char *const envp[])
{
    int		id;
    int		i;
    int		flag;
	int		size;
    char	**path;
	char	*file;
	t_cmd	cmd1;
	char	**args1;
	
   // checks_errors(argc);
   // test_files(argv);
    //bringing the var PATH from envp :
    i = 0;
    flag = 0;
	//this part is worked well
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH", 4) == 0)
        {
            path = ft_split(envp[i], ':');
            path[0] = ft_strtrim(path[0], "PATH=");
            break;
        }
        i++;
    }
	
	// printf("Output envp |||\n");
	// int j = 0;
	// while (path[j])
	// {
	// 	printf("path[%d] == %s\n", j, path[j]);
	// 	j++;
	// }
	
	//putting the file1 into a string to send him to args(for excev fct):
	//this part is worked well
	file = (char *)malloc(sizeof(char) * 1);
	file[0] = '\0';
	file_into_str(argv[1], &file);
	//printf("file1 : \n%s\n", file);
	
    // //fill the cmd1 with the path ,cmd and his parameters , and file1 :
	// //first of all must calcul how many args we have , for allocating the tab cmd1:
	cmd_parameters(argv, &cmd1);
	size = cmd1.lines + 3;
	//printf("size is %d\n", size);
	//printf("lines of cmd1 is %d\n", cmd1.lines);
	args1 = (char **) malloc(sizeof(char *) * (size));
	if (args1 == NULL)
		ft_exit();
	// //allocating_space(&args1, path, argv, cmd1);
	// //hena fash kay segfaulti 7it dakshi lfog kamel khedam  
	creating_args(&args1, file, cmd1, size);
	path = concat_pathwithcmd(path, cmd1);
	// printf("******* output the paths *******\n");
	// 	int j = 0;
	// 	while (path[j])
	// 	{
	// 		printf("path[%d] == %s\n\n", j, path[j]);
	// 		j++;
	// 	}
	
	//starting process using fork and execve and pipe dup ..
	
    id = fork();
	i = 0;
    if (id < 0)
        perror("ERROR");
    //child process :
    else if (id == 0)
    {
        //should do here the first execeve function to execute the cmd1
        //checking is the command exits in some of the paths by using execeve :
        while (path[i])
        {
			flag = 0;
			args1[0] = path[i];
			//printf("args[0] == %s\n", args1[0]);
            if (execve(path[i], args1, NULL) == -1)
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
	// printf("******* output the args *******\n");
	// 	int j = 0;
	// 	while (args1[j])
	// 	{
	// 		printf("args[%d] == %s\n\n", j, args1[j]);
	// 		j++;
	// 	}
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