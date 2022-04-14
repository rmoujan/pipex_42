/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:46:12 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/14 16:32:44 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main()
{
    char **str;

    str = (char **)malloc(sizeof(char *) * 3);
    int i = 0;
    while (i < 3)
    {
         str[i] = (char *)malloc(sizeof(char ) * 10);
         i++;
    }
    str[i] = NULL;
    i = 0;
    str[i]="hallo";
    while (str[i])
    {
        printf("str[%d] == %s \n", i, str[i]);
        printf("test \n");
        i++;
    }
    return 0;
}