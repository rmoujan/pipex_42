/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:28:17 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/07 17:45:26 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	checks_errors(int argc)
{
	if (argc != 5)
	{
		write(1, "ERROR MANAGEMENT \n", 18);
		exit(1);
	}
}

void	test_files(char *argv[])
{
	if (access(argv[1], F_OK) == -1
		|| access(argv[1], R_OK | W_OK | X_OK) == -1)
	{
		write(1, "ERROR OCCURED WHEN CHECKING FILES \n", 35);
		exit(1);
	}
	if (access(argv[4], F_OK) == -1
		|| access(argv[4], R_OK | W_OK | X_OK) == -1)
	{
		write(1, "ERROR OCCURED WHEN CHECKING FILES \n", 35);
		exit(1);
	}
}
