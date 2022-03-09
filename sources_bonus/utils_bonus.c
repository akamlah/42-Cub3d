/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:11:44 by agebert           #+#    #+#             */
/*   Updated: 2022/03/09 00:11:45 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

t_vector2	new_vector2(double x, double y)
{
	t_vector2	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	return (new_vector);
}

t_vector2_int	new_vector2_int(int x, int y)
{
	t_vector2_int	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	return (new_vector);
}
