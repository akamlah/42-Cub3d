/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_check_borders_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:03:36 by agebert           #+#    #+#             */
/*   Updated: 2022/03/09 01:23:13 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

static int	check_top_bot(t_vars *vars, char **maplines)
{
	int	y;
	int	x;

	y = vars->map->n_lines - 1;
	x = 0;
	while (maplines[0][x] && x < (int)ft_strlen(maplines[0]) - 2)
	{
		if (maplines[0][x] != '1' && maplines[0][x] != ' ')
		{
			printf("Error\nMap: not inclosed in walls (x: %d, y: %d)\n", x, 0);
			return (1);
		}
		x++;
	}
	x = 0;
	while (maplines[y][x] && x < (int)ft_strlen(maplines[y]) - 2)
	{
		if (maplines[y][x] != '1' && maplines[y][x] != ' ')
		{
			printf("Error\nMap: not inclosed in walls (x: %d, y: %d)\n", x, y);
			return (1);
		}
		x++;
	}
	return (0);
}

static int	check_front(char **maplines, int y)
{
	int	x;

	x = 0;
	while (maplines[y][x] && maplines[y][x] == ' ')
			x++;
	if (maplines[y][x] != '1')
	{
		printf("Error\nMap: not inclosed in walls (x: %d, y: %d)\n", x, y);
		return (1);
	}
	return (0);
}

static int	check_back(char **maplines, int y)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = (int)ft_strlen(maplines[y]);
	while (maplines[y][line_len - 2 - i]
		&& maplines[y][line_len - 2 - i] == ' ')
			i++;
	if (maplines[y][line_len - 2 - i] != '1')
	{
		printf("Error\nMap: not inclosed in walls (x: %d, y: %d)\n", \
		line_len - 2 - i, y);
		return (1);
	}
	return (0);
}

int	check_borders(t_vars *vars, char **maplines)
{
	int	y;

	y = 0;
	while (maplines[y])
	{
		if (check_front(maplines, y)
			|| check_back(maplines, y))
			return (1);
		y++;
	}
	if (check_top_bot(vars, maplines))
		return (1);
	return (0);
}
