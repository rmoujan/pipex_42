/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:32:06 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/23 00:26:03 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_argument	t_arg;
struct s_argument{
	char	**path;
	char	**cmd;
};

typedef struct s_fds		t_fds;
struct s_fds{
	pid_t	frk1;
	pid_t	frk2;
	int		argc;
	t_arg	**prg;
	int		**pii;
	int		fd1;
	int		fd2;
	int		pi[2];
	int		pidoc[2][2];
};

typedef struct s_fdbns		t_fdbns;
struct s_fdbns{
	int		fd1;
	int		fd2;
};

//*** maindatory part for pipex ***//

void	checks_errors(int argc);
void	test_files(char *argv[]);
void	fct(char **argv, int file);
void	checks_errors(int argc);
void	ft_exit(void);
void	test_files(char *argv[]);
void	check_exist_cmd(t_arg *prg1);
void	first_process(t_fds id, t_arg *prg1, char *const envp[]);
void	second_process(t_fds id, t_arg *prg2, char *const envp[]);
void	begin_forking(t_fds id, t_arg *prg1, t_arg *prg2, char *const envp[]);
void	ft_check(t_arg *prg);
int		ft_calcul(char *str);
void	close_main(t_fds id);

//*** bonus part for pipex "multiple pipes" ***//

void	checks_errormltpipe(int argc);
void	check_exist_cmdbns(t_arg **prg);
void	getting_paths_bns(char *const envp[], t_arg **prg);
void	concaten_pathscmd_bns(t_arg **prg, char **argv);
void	ft_checkbns(t_arg **prg);
void	multiple_pipe(int argc, char *argv[], char *const envp[]);
void	checks_errormltpipe(int argc);
void	close_mltpipes1(t_fds id, int i);
void	multpipes_chunk1(t_fds id, char *argv[], char *const envp[]);
void	forking_mltpipes(t_fds id, char *const envp[]);
void	mlt_pipes2(int argc, char *argv[], char *const envp[], t_fds id);

//*** bonus part for pipex "heredoc" ***//

void	close_heredoc(t_fds id);
void	forking_heredoc(t_fds id, t_arg *prg1, t_arg *prg2, char *const envp[]);
void	errors_heredoc(int argc);
void	ft_heredoc(int argc, char *argv[], char *const envp[]);
void	concaten_pathscmd(t_arg *prg, char *argv);
void	getting_paths(char *const envp[], t_arg *prg);
void	get_input_herdoc(t_fds *id, char *argv);
void	ft_error(char *str);

/// libft's functions //

char	*ft_strjjoin(char **s1, char **s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
int		ft_checker(char *str);
char	*ft_process(char **rest);
void	*ft_free(char **p1);
char	*ft_work(char **buffer, char **rest, int fd);
#endif
