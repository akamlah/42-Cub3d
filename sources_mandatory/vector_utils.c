/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:30:36 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/08 23:30:37 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_mandatory/cub3d_mandatory.h"

t_vector2	new_vector2(double x, double y)
{
	t_vector2	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	return (new_vector);
}
