/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:30:22 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/19 17:37:40 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//# include <fcntl.h> 
# include <stdlib.h> 
# include <unistd.h>
#define BUFFER_SIZE 5

char		*get_next_line(int fd);
char		*ft_strjoin1(char **s1, char **s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *str);
int			ft_checker(char *str);
char		*ft_process(char **rest);
void		*ft_free(char **p1);
char		*ft_work(char **buffer, char **rest, int fd);

#endif