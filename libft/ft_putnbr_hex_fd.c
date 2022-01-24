/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 14:13:16 by akamlah           #+#    #+#             */
/*   Updated: 2021/08/25 21:30:09 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

/* This function takes an integer as input and writes it to the given
filedescriptor as ascii character and in hexadecimal form with lowercase
letters.*/

void	ft_putnbr_hex_fd(long n, int fd)
{
	if (n < 16)
	{
		if (n % 16 < 10)
			ft_putchar_fd(n % 16 + 48, 1);
		if (n % 16 >= 10)
			ft_putchar_fd(n % 16 + 48 + 39, 1);
	}
	if (n >= 16)
	{
		ft_putnbr_hex_fd(n / 16, fd);
		ft_putnbr_hex_fd(n % 16, fd);
	}
}
