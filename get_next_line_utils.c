/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:04:30 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/04 15:57:04 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_copy(char const *s1, char const *s2, char *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		p[i] = s2[j];
		j++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

char	*ft_strjjoin(char **s1, char **s2)
{
	char	*p;

	if (!*s1 || !*s2)
		return (NULL);
	p = malloc((ft_strlen(*s1) + ft_strlen(*s2) + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	p = ft_copy(*s1, *s2, p);
	ft_free(s1);
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	p = malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	if (start <= ft_strlen(s))
	{
		while (i < len && s)
		{
			p[i] = s[start];
			i++;
			start++;
		}
	}
	p[i] = '\0';
	return (p);
}
