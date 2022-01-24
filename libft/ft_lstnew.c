/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:09:55 by akamlah           #+#    #+#             */
/*   Updated: 2021/08/25 15:26:42 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

/* Allocates (with malloc(3)) and returns a new
element. The variable ’content’ is initialized
with the value of the parameter ’content’. The
variable ’next’ is initialized to NULL. */

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = 0;
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	(*new).content = content;
	(*new).next = 0;
	return (new);
}
