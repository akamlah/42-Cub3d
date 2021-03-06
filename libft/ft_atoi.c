/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 09:51:41 by akamlah           #+#    #+#             */
/*   Updated: 2021/06/28 09:51:54 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	long	n;
	size_t	nlen;

	sign = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	nlen = 0;
	n = 0;
	while (str[nlen] <= '9' && str[nlen] >= '0')
	{
		n = n * 10 + str[nlen] - 48;
		nlen++;
	}
	return (sign * n);
}
