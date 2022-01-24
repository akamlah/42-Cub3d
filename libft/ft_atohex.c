/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:18:42 by akamlah           #+#    #+#             */
/*   Updated: 2021/09/21 16:18:56 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

/*
**	scans through string, skipping blanks (ascii 9-13 and space)
**	finds first '0' occurrence after that, chackes that following is
**	'x' and takes the hexsdecimal digits following returning an
**	integer with the actual value of the number as a decimal int.
**	for maximal 6 digit hexadecimals.
*/
unsigned int	ft_atohex(const char *str)
{
	unsigned long	n;
	size_t			nlen;

	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	if (*str == '0')
		str++;
	if (*str == 'x')
		str++;
	nlen = 0;
	n = 0;
	while (((str[nlen] <= '9' && str[nlen] >= '0') \
		|| (str[nlen] <= 'F' && str[nlen] >= 'A' ) \
		|| (str[nlen] <= 'f' && str[nlen] >= 'a' )) && (nlen < 7))
	{
		if (str[nlen] <= '9' && str[nlen] >= '0')
			n = n * 16 + str[nlen] - '0';
		if (str[nlen] <= 'F' && str[nlen] >= 'A')
			n = n * 16 + str[nlen] - 55;
		else if (str[nlen] <= 'f' && str[nlen] >= 'a')
			n = n * 16 + str[nlen] - 87;
		nlen++;
	}
	return (n);
}

/* 
int main()
{
	//	DEBUG (in while loop):
	//	int c = str[nlen];
	//	printf("char is: %d\n", c);
	char str[] = "stocazzo,0xffffff";
//	printf("%d\n", ft_atohex("0xffffff"));
	printf("%d\n", ft_atohex(ft_strchr(str, 'x')));
} */