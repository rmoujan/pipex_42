/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:28 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/23 02:07:54 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	ft_exit(void)
{
	write(1, "ERROR MANAGEMENT\n", 17);
	exit(1);
}

int	main(int argc, char *argv[], char *const envp[])
{
	t_fds	id;
	t_arg	*prg1;
	t_arg	*prg2;

	checks_errors(argc);
	prg1 = (t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg1);
	concaten_pathscmd(prg1, argv[2]);
	prg2 = (t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg2);
	concaten_pathscmd(prg2, argv[3]);
	id.fd1 = open(argv[1], O_RDWR | O_CREAT, 0666);
	id.fd2 = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
	begin_forking(id, prg1, prg2, envp);
	// int i = 0;
	// printf("insid MAIN\n");
	// while (prg1->cmd[i])
	// {
	// 	printf("**prg1->cmd[%d]== %s**\n",i , prg1->cmd[i]);
	// 	i++;
	// }
	//  i = 0;
	//  printf("\\\\\\\\\\\\\\\n");
	// while (prg1->path[i])
	// {
	// 	printf("**prg1->path[%d]== %s**\n",i , prg1->path[i]);
	// 	i++;
	// }
	// 	 i = 0;
	// printf("PRG2\n");
	// while (prg2->cmd[i])
	// {
	// 	printf("**prg2->cmd[%d]== %s**\n",i , prg2->cmd[i]);
	// 	i++;
	// }
	//  i = 0;
	//  printf("\\\\\\\\\\\\\\\n");
	// while (prg1->path[i])
	// {
	// 	printf("**prg2->path[%d]== %s**\n",i , prg2->path[i]);
	// 	i++;
	// }
	return (0);
}
