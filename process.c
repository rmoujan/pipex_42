/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:29:53 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/03 13:38:33 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void fct(char **argv, int file)
{
    int fr;

    fr = fork();

    if (fr == -1)
        perror("fork");
    //child process :
    else if (fr == 0)
    {
        if (exceve(argv[3], argv + 3, "file3.txt", NULL) == -1)
            perror("execve");
    }
    //parent process 
    else
    {
        printf("parent process \n");   
    }
}