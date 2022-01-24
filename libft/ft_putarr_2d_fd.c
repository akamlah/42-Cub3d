/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarr_2d_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 21:08:20 by akamlah           #+#    #+#             */
/*   Updated: 2021/08/25 21:14:58 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Prints a string os trings, strung by string separated by a newline, to the
given file descriptor. */

void	ft_putarr_d2_fd(char **arr, int fd)
{
	int	i;

	i = 0;
	if (arr == NULL || arr[i] == NULL)
		return ;
	while (arr[i] != NULL)
	{
		ft_putendl_fd(arr[i], fd);
		i++;
	}
}
