/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:21:51 by akamlah           #+#    #+#             */
/*   Updated: 2021/06/28 11:34:54 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static size_t	ft_itostr(int n, long num)
{
	size_t	l;

	l = 0;
	while (num != 0)
	{
		l++;
		num = num / 10;
	}
	if (n < 0 || n == (-0))
		l += 1;
	return (l);
}

char	*ft_itoa(int n)
{
	size_t	l;
	long	num;
	char	*nstr;

	num = (long)n;
	l = ft_itostr(n, num);
	nstr = (char *)malloc(sizeof(char) * (l + 1));
	if (!nstr)
		return (0);
	nstr[l] = '\0';
	if (n < 0)
		num = (long)n * -1;
	else
		num = (long)n;
	while (l--)
	{
		nstr[l] = (num % 10) + 48;
		num = num / 10;
	}
	if (n < 0)
		nstr[0] = '-';
	return (nstr);
}
