/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teststrjoinwithgnl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:48:58 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/04 16:03:19 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"


int main(int argc, char *argv[])
{
    int		fd;
	char	*str;
    char *file;

	fd = open(argv[1], O_RDWR);
   // printf("fd == %d\n", fd);
	str = get_next_line(fd);
    file = (char *)malloc(sizeof(char) * 1);
	file[0] = '\0';
   // printf("outside loop == %s \n", str);
	while (str)
	{
       // printf("str == %s\n", str);
		file = ft_strjoin(file, str);
		//free(str);
		//free(file);
		str = get_next_line(fd);
	}
    printf("%s\n", file);
}