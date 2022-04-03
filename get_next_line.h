/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan <rmoujan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:19:29 by rmoujan           #+#    #+#             */
/*   Updated: 2021/12/10 20:15:45 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//# include <fcntl.h> 
# include <stdlib.h> 
# include <unistd.h>

char		*get_next_line(int fd);
char		*ft_strjoin(char **s1, char **s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *str);
int			ft_checker(char *str);
char		*ft_process(char **rest);
void		*ft_free(char **p1);
char		*ft_work(char **buffer, char **rest, int fd);

#endif