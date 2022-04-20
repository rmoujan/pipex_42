/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:28:03 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/20 02:07:59 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"

// ./pipex here_doc LIMITER cmd cmd1 file :::
void ft_heredoc(int argc, char *argv[], char *const envp[])
{
    t_fds	id;
	t_arg	*prg1;
	t_arg	*prg2;
    
    //first of all : checks all errors :
    errors_heredoc(argc);
    //preparing cmd :
	prg1 = (t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg1);
	concaten_pathscmd(prg1, argv[3]);
	prg2 = (t_arg *) malloc(sizeof(t_arg));
	getting_paths(envp, prg2);
	concaten_pathscmd(prg2, argv[4]);
	check_exist_cmd(prg1, prg2);
	id.fd2 = open(argv[5], O_RDWR | O_APPEND | O_CREAT, 0666);
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
    //when the input is from HEREDOC :
    //starting herdoc:
	get_input_herdoc(id, argv[2]);
	forking_heredoc(id, prg1, prg2, envp);
}