/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:28:03 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/20 02:42:01 by rmoujan          ###   ########.fr       */
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
	// get_input_herdoc(id, argv[2]);
	char *str;
    if (pipe(id.pidoc[0]) == -1)
		ft_error("pipe");
    write(0,"heredoc>", 8);
	str = get_next_line(0);
	str = ft_strtrim(str, "\n");
	while (strcmp(str, argv[2]) != 0)
	{
		str = ft_strjoin(str, "\n");
		write(0,"heredoc>", 8);
		write(id.pidoc[0][1], str, ft_strlen(str));
		free(str);
		str = get_next_line(0);
		str = ft_strtrim(str, "\n");	
	}
	close(id.pidoc[0][1]);
	read(id.pidoc[0][0], str, 1000);
	printf("***%s***\n", str);
	forking_heredoc(id, prg1, prg2, envp);
}

///NOTES : FASH KANSIFT PIPE L FCT B7ALI KAY LOSE DATA LI MESTORYA FIH
///NOTES2: HERE DOC IS NOT WORKING CUZ THE FIRST PIPE DON'T SAVE THE DATA WELL