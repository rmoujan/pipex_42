/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:32:06 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/05 16:03:35 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 5

typedef struct s_command t_cmd;
struct s_command{
    char **name;
    int lines;
};

typedef struct s_argument t_arg;
struct s_argument{
    char **args;
    char **path;
    t_cmd cmd;
};

void checks_errors(int argc);
void test_files(char *argv[]);
void fct(char **argv, int file);



char		*get_next_line(int fd);
char		*ft_strjjoin(char **s1, char **s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *str);
int			ft_checker(char *str);
char		*ft_process(char **rest);
void		*ft_free(char **p1);
char		*ft_work(char **buffer, char **rest, int fd);


#endif
