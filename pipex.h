/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:32:06 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/09 10:25:35 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
// # define BUFFER_SIZE 5

typedef struct s_argument	t_arg;
struct s_argument{
	char	**path;
	char	**cmd;
};

typedef struct s_fds	t_fds;
struct s_fds{
    pid_t	frk1;
	pid_t	frk2;
    int		fd1;
    int		fd2;
	int		pi[2];
};

void	checks_errors(int argc);
void	test_files(char *argv[]);
void	fct(char **argv, int file);
void	checks_errors(int argc);
void	test_files(char *argv[]);
void	check_exist_cmd(t_arg *prg1, t_arg *prg2);
char	*ft_strjjoin(char **s1, char **s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
int		ft_checker(char *str);
char	*ft_process(char **rest);
void	*ft_free(char **p1);
char	*ft_work(char **buffer, char **rest, int fd);
#endif
