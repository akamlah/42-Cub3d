/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 11:26:43 by akamlah           #+#    #+#             */
/*   Updated: 2021/06/25 13:16:18 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*memptr;

	memptr = (char *)malloc(sizeof(char) * count * size);
	if (!memptr)
		return (0);
	ft_bzero(memptr, (count * size));
	return ((void *)memptr);
}
