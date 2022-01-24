/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_first_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:52:06 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/11 18:05:21 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_get_first_word(char *str)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	word = ft_substr(str, 0, i);
	return (word);
}
