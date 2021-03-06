/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_check_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:31:05 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/15 00:38:31 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_mandatory/cub3d_mandatory.h"

static int	check_lr_space(char **maplines, t_vector2_int pos)
{
	int	length_middle;

	length_middle = (int)ft_strlen(maplines[pos.y]) - 2;
	if ((pos.x != 0 \
		&& maplines[pos.y][pos.x - 1] != '1' \
		&& maplines[pos.y][pos.x - 1] != ' ') \
		|| ((pos.x < length_middle
		&& maplines[pos.y][pos.x + 1] != '1' \
		&& maplines[pos.y][pos.x + 1] != ' ') \
		))
		return (1);
	else
		return (0);
}

static int	check_valid_chars(t_vars *vars, char **maplines, t_vector2_int pos)
{
	if (!check_bot(vars, maplines, pos, '0') \
		&& !check_top(maplines, pos, '0') \
		&& !check_lr(maplines, pos, '0'))
		return (0);
	return (1);
}

static int	is_spawn(char c)
{
	char	*valid_c;
	int		i;

	valid_c = "NSEW";
	i = 0;
	while (valid_c[i])
	{
		if (c == valid_c[i])
			return (1);
		i++;
	}
	return (0);
}

static int	check_square(t_vars *vars, char **maplines, t_vector2_int pos)
{
	if ((maplines[pos.y][pos.x] == ' '
		&& (check_bot_space(vars, maplines, pos) \
		|| check_top_space(maplines, pos) \
		|| check_lr_space(maplines, pos))) \
		||
		((maplines[pos.y][pos.x] == '0' \
		|| maplines[pos.y][pos.x] == 'N' \
		|| maplines[pos.y][pos.x] == 'S' \
		|| maplines[pos.y][pos.x] == 'E' \
		|| maplines[pos.y][pos.x] == 'W') \
		&& check_valid_chars(vars, maplines, pos)))
	{
		printf("Error\nMap: Incorrect format at (x: %d, y: %d) \
not enclosed by walls\n", pos.x, pos.y);
		return (1);
	}
	return (0);
}

int	check_map(t_vars *vars, char **maplines)
{
	t_vector2_int	pos;
	int				spawncnt;

	pos.y = 0;
	pos.x = 0;
	spawncnt = 0;
	while (maplines[pos.y])
	{
		while (maplines[pos.y][pos.x])
		{
			if (is_spawn(maplines[pos.y][pos.x]))
				spawncnt++;
			if (check_square(vars, maplines, pos))
				return (1);
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
	if (spawncnt != 1)
	{
		printf("Error\nMap: Incorrect number of \
				spawnpoints, only 1 allowed!\n");
		return (1);
	}
	return (0);
}
