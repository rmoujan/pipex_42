/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:28 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/11 11:09:14 by rmoujan          ###   ########.fr       */
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
		prg->path[i] = ft_strjoin(prg->path[i] , prg->cmd[0]);
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

int main(int argc, char *argv[], char *const envp[])
{
    t_fds   id;
	t_arg	*prg1;
	t_arg	*prg2;
    
    checks_errors(argc);
	prg1 =(t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg1);
	concaten_pathscmd(prg1, argv[2]);
    prg2 =(t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg2);
	concaten_pathscmd(prg2, argv[3]);
    check_exist_cmd(prg1, prg2);
	id.fd1 = open(argv[1], O_RDWR | O_CREAT);
    id.fd2 = open(argv[4], O_RDWR | O_TRUNC | O_CREAT);
    
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
    else if (id.frk1 == 0)
		first_process(id, prg1, envp);
    else
    {
        id.frk2 = fork();
        if (id.frk2 < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (id.frk2 == 0)
			second_process(id, prg2, envp);
		else
        {
            ft_close(id);
           	waitpid(id.frk1, NULL, 0);
            waitpid(id.frk2, NULL, 0);
	    }
     }
    return (0);
}