/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testpointer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmoujan < rmoujan@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:04:23 by rmoujan           #+#    #+#             */
/*   Updated: 2022/04/04 17:05:28 by rmoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>


void update(char *ptr)
{
  *ptr="world";
}

int main() {
  
  char *str;
  str = (char *) malloc( sizeof(char) * 6);
  str = "hallo";
  
  printf("%s\n", str);
  update(&str);
  printf("%s\n", str);
  return 0;
}