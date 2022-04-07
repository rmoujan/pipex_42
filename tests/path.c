/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:55:11 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/03 17:35:31 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unsitd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./libft/libft.h"

///Note : bash t3yti lfile kayn fe directory bo7do ... fa rah darori khaski
// t includi ba3eda had dossier like that : #include "./libft/libft.h" ... 
// mn be3d fash teji lcompilation khaski darori ay fct st3mltiha compiliha like that : 
// gcc libft/ft_split.c libft/ft_strdup.c libft/ft_strchr.c libft/ft_strtrim.c 
// libft/ft_strncmp.c  libft/ft_strlen.c libft/ft_substr.c path.c

int main(int argc, char *argv[], char *envp[])
{
    int i = 0;
    char **tab;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH", 4) == 0)
        {
            tab = ft_split(envp[i], ':');
            tab[0]=ft_strtrim(tab[0], "PATH=");
            break;
        }
        i++;
    }
    i = 0;
    while (tab[i])
    {
        //if(i == 0)
        //tab[i] = ft_strtrim(tab[i], "PATH=");
        printf("%s\n", tab[i]);
        i++;
    } 
}


// int	ft_strncmp(const char *first, const char *second, size_t l)
// {
// 	unsigned char	*p1;
// 	unsigned char	*p2;
// 	size_t			i;

// 	i = 0;
// 	p1 = (unsigned char *)first;
// 	p2 = (unsigned char *)second;
// 	while ((p1[i] != '\0' || p2[i] != '\0') && (i < l))
// 	{
// 		if (p1[i] > p2[i])
// 			return (p1[i] - p2[i]);
// 		else if (p1[i] < p2[i])
// 			return (p1[i] - p2[i]);
// 		i++;
// 	}
// 	return (0);
// }

// static int	c_words(char const *s1, char c)
// {
// 	int	i;
// 	int	total;

// 	i = 0;
// 	total = 0;
// 	while (s1[i] == c)
// 		i++;
// 	while (s1[i] != '\0')
// 	{
// 		if (s1[i] == c && s1[i + 1] != c)
// 			total++;
// 		i++;
// 	}
// 	if (i != 0)
// 	{
// 		if (s1[i - 1] != c)
// 			total++;
// 	}
// 	return (total);
// }

// static char	*ft_cpy(char const *s1, int k, int j)
// {
// 	int		size;
// 	int		i;
// 	char	*p;

// 	size = (j - k) + 1;
// 	i = 0;
// 	p = malloc (size * sizeof(char));
// 	if (p == NULL)
// 		return (NULL);
// 	while (k < j)
// 	{
// 		p[i] = s1[k];
// 		i++;
// 		k++;
// 	}
// 	p[i] = '\0';
// 	return (p);
// }

// static void	ft_free(char **tab, int i)
// {
// 	int	j;

// 	j = 0;
// 	while (j < i)
// 	{
// 		free(tab[j]);
// 		j++;
// 	}
// 	free(tab);
// }

// static char	**f_str(char const *s1, char c, char **tab)
// {
// 	int	i;
// 	int	k;
// 	int	j;

// 	i = 0;
// 	k = -1;
// 	while (s1[++k] != '\0')
// 	{
// 		if (s1[k] != c)
// 		{
// 			j = k;
// 			while (s1[j] != c && s1[j] != '\0')
// 				j++;
// 			tab[i] = ft_cpy(s1, k, j);
// 			if (!(tab[i]))
// 			{
// 				ft_free(tab, i);
// 				return (NULL);
// 			}
// 			i++;
// 			k = j - 1;
// 		}
// 	}
// 	tab[i] = NULL;
// 	return (tab);
// }

// char	**ft_split(char const *s1, char c)
// {
// 	char	**tab;

// 	if (!s1)
// 		return (NULL);
// 	tab = malloc ((c_words(s1, c) + 1) * sizeof(char *));
// 	if (c_words(s1, c) == 0)
// 	{
// 		tab[0] = NULL;
// 		return (tab);
// 	}
// 	if (tab == NULL)
// 		return (NULL);
// 	return (f_str(s1, c, tab));
// }
// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// // }
// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*p;
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	if (len >= ft_strlen(s))
// 		len = ft_strlen(s);
// 	p = malloc((len + 1) * sizeof(char));
// 	if (p == NULL)
// 		return (NULL);
// 	if (start <= ft_strlen(s))
// 	{
// 		while (i < len && s)
// 		{
// 			p[i] = s[start];
// 			i++;
// 			start++;
// 		}
// 	}
// 	p[i] = '\0';
// 	return (p);
// }
// char	*ft_strdup(const char *src)
// {
// 	char	*ptr;
// 	int		i;
// 	int		src_l;

// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		i++;
// 	}
// 	src_l = i + 1;
// 	ptr = (char *)malloc(src_l * sizeof(char));
// 	if (ptr == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		ptr[i] = src[i];
// 		i++;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// // }
// char	*ft_strchr(const char *s, int c)
// {
// 	char	cara;
// 	int		i;
// 	int		j;
// 	char	*p1;

// 	i = 0;
// 	j = 0;
// 	p1 = (char *)s;
// 	cara = (char)c;
// 	while (p1[i] != '\0')
// 	{
// 		if (p1[i] == cara)
// 			return (&p1[i]);
// 		i++;
// 	}
// 	if (c == '\0')
// 	{
// 		while (p1[j] != '\0')
// 			j++;
// 		return (&p1[j]);
// 	}
// 	return (NULL);
// }

// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	char			*p;
// 	unsigned int	len1;
// 	unsigned int	i;

// 	i = 0;
// 	p = NULL;
// 	if (!s1 || !set)
// 		return (NULL);
// 	if (*s1 == '\0')
// 		return (ft_strdup(""));
// 	len1 = ft_strlen(s1) - 1;
// 	while (ft_strchr(set, s1[i]) && i <= len1)
// 		i++;
// 	while (ft_strchr(set, s1[len1]) && len1 >= i)
// 		len1--;
// 	p = ft_substr(s1, i, (len1 - i + 1));
// 	return (p);
// }
