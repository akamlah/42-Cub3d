/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_char2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:54:03 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/11 18:05:06 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_free_char2(char **m)
{
	int	i;

	i = 0;
	while (m[i] != NULL)
	{
		free(m[i]);
		i++;
	}
	if (m != NULL)
		free(m);
}
