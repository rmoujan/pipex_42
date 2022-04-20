/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:30:27 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/20 18:25:36 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"

void errors_heredoc(int argc)
{
    if (argc != 6)
    {
        write(1, "ERROR MANAGEMENT \n", 18);
		exit(1);
    }
}

//get the input from heredoc and store it into the pipe pi[0][1]
void get_input_herdoc(t_fds id, char *argv)
{
	char *str;
	
    if (pipe(id.pidoc[0]) == -1)
		ft_error("pipe");
    write(0,"heredoc>", 8);
	str = get_next_line(0);
	str = ft_strtrim(str, "\n");
	while (strcmp(str, argv) != 0)
	{
		str = ft_strjoin(str, "\n");
		write(0,"heredoc>", 8);
		write(id.pidoc[0][1], str, ft_strlen(str));
		free(str);
		str = get_next_line(0);
		str = ft_strtrim(str, "\n");	
	}
	//close(id.pidoc[0][1]);
	//read(id.pidoc[0][0], str, 1000);
	//printf("***%s***\n", str);
}
