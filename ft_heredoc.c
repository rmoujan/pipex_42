/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:28:03 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/21 18:28:31 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"

//./pipex here_doc LIMITER cmd cmd1 file :::
void	ft_heredoc(int argc, char *argv[], char *const envp[])
{
	t_fds	id;
	t_arg	*prg1;
	t_arg	*prg2;

	errors_heredoc(argc);
	prg1 = (t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg1);
	concaten_pathscmd(prg1, argv[3]);
	prg2 = (t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg2);
	concaten_pathscmd(prg2, argv[4]);
	check_exist_cmd(prg1, prg2);
	id.fd2 = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
	get_input_herdoc(&id, argv[2]);
	forking_heredoc(id, prg1, prg2, envp);
	// int i = 0;
	// while (prg1->cmd[i])
	// {
	// 	//printf("**%s**\n", prg1->path[i]);
	// 	free(prg1->cmd[i]);
	// 	i++;
	// }
	// while (prg2->cmd[i])
	// {
	// 	//printf("**%s**\n", prg1->path[i]);
	// 	free(prg2->cmd[i]);
	// 	i++;
	// }
	// i = 0;
	// while(prg1->path[i])
	// {
	// 	printf("**%s**\n", prg1->path[i]);
	// 	i++;
	// }
	
	// //free(prg1->path[0]);
	// //free(prg1->path[1]);
	// free(prg1->path);
	// free(prg2->path);
	// free(prg1);
	// free(prg2);
	
	
	// while(1)
	// {
		
	// }
}
