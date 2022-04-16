/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:39:34 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/16 13:50:19 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main()
{
    int tab[10]={1,8,6,9,10,88,99,700,900,1};
    int i = 0;
    while (i < 10)
    {
        if (tab[i] == 1 && i != 0 )
        {
            printf("from first case and i ==  %d ** %d\n",i, tab[i]);
        }
        else if (tab[9] == 1)
        {
            printf("from last case and i == %d ** %d \n",i, tab[i]);
        }
         else if (tab[i] != 1)
            printf("from mid casees and i == %d ** %d\n", i , tab[i]);
        i++;
    }
}