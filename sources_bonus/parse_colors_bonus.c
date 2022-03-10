/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:34:40 by agebert           #+#    #+#             */
/*   Updated: 2022/03/10 16:01:45 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

/*
	Return s 0 (FALSE) if wrong format (other chars than comma or digits,
	or wron order, or too many/ too few commas or digits)
	Returns 1 if the checking is passed.
*/
int	str_is_good_format(char *s)
{
	int	i;
	int	comma;
	int	digit;

	i = 0;
	comma = 0;
	digit = 0;
	while (s[i])
	{
		if (s[i] != ',' && !ft_isdigit(s[i]))
			return (0);
		if (s[i] == ',')
		{
			comma ++;
			if ((digit == 0 || !s[i + 1] || i == 0) || ((i != 0 && s[i + 1])
					&& (!ft_isdigit(s[i - 1]) || !ft_isdigit(s[i + 1]))))
				return (0);
		}
		if (ft_isdigit(s[i]))
			digit ++;
		i++;
	}
	if (comma != 2 || digit < 3 || digit > 9)
		return (0);
	return (1);
}

/*
	Returns 1 if n is rgb (integer between 0 and 255)
	Returns 0 if not.
*/
int	is_rgb(int n)
{
	if (n < 0 || n > 255)
		return (0);
	return (1);
}

/*
	Checks and parses a string as a color value.
	Return s 0 (FALSE) if wrong format or not rgb values are found.
	Else it converts the rgb values to integers and then composes the
	rgb color value as decimal int and writes it to *dst.
*/
int	parse_color(char *color, int *dst)
{
	int	r;
	int	g;
	int	b;

	if (!str_is_good_format(color))
		return (0);
	r = ft_atoi(color);
	color = ft_strchr(color, ',') + 1;
	g = ft_atoi(color++);
	color = ft_strchr(color, ',') + 1;
	b = ft_atoi(color++);
	if (!is_rgb(r) || !is_rgb(g) || !is_rgb(b))
		return (0);
	*dst = r * 256 * 256 + g * 256 + b;
	return (1);
}

/*
	Return s 0 (FALSE) if wrong format or not rgb values are found.
*/
int	parse_colors(t_vars *vars)
{
	if (!parse_color(vars->map->floor_color, &vars->floor_color))
	{
		printf("Error\nWrong color format\n");
		return (0);
	}
	if (!parse_color(vars->map->ceiling_color, &vars->ceiling_color))
	{
		printf("Error\nWrong color format\n");
		return (0);
	}
	return (1);
}
