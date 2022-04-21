/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:31:28 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/21 15:37:32 by rmoujan          ###   ########.fr       */
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
	check_exist_cmd(prg1, prg2);
	id.fd1 = open(argv[1], O_RDWR | O_CREAT, 0666);
	id.fd2 = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (id.fd1 == -1 || id.fd2 == -1)
		ft_exit();
	begin_forking(id, prg1, prg2, envp);
	return (0);
}
