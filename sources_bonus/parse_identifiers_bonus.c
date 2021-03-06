/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:03:30 by agebert           #+#    #+#             */
/*   Updated: 2022/03/14 19:02:38 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

int	is_whitespaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	handle_tex_id(int i, char *id, char *line, t_map *map)
{
	char	**map_ptr;
	int		j;

	j = 2;
	if (id[0] == 'N')
		map_ptr = &(map->textr_n);
	if (id[0] == 'S')
		map_ptr = &(map->textr_s);
	if (id[0] == 'W')
		map_ptr = &(map->textr_w);
	if (id[0] == 'E')
		map_ptr = &(map->textr_e);
	if (*map_ptr)
	{
		printf("Error\nLine %d: Duplicate: identifier `%s'\n", i + 1, id);
		map->subf_error = 1;
		return (0);
	}
	while (line[j] == ' ')
		j++;
	if (line[j])
		*map_ptr = ft_strdup(line + j);
	return (1);
}

int	get_texture(char *line, t_map *map, int i)
{
	if (!line[0] || !line[1] || !line[2])
		return (0);
	if (line [2] != ' ')
		return (0);
	if (line[0] == 'N' && line[1] == 'O')
		return (handle_tex_id(i, "NO", line, map));
	if (line[0] == 'S' && line[1] == 'O')
		return (handle_tex_id(i, "SO", line, map));
	if (line[0] == 'W' && line[1] == 'E')
		return (handle_tex_id(i, "WE", line, map));
	if (line[0] == 'E' && line[1] == 'A')
		return (handle_tex_id(i, "EA", line, map));
	return (0);
}

static int	error_duplicate_color_id(t_map *map, int i, char *id)
{
	printf("Error\nLine %d: Duplicate: identifier `%s'\n", i + 1, id);
	map->subf_error = 1;
	return (0);
}

int	get_color_id(char *line, t_map *map, int i)
{
	int	j;

	j = 2;
	if (!line[0] || !line[1])
		return (0);
	if (line [1] != ' ')
		return (0);
	while (line[j] == ' ')
		j++;
	if (line[0] == 'F' && line[j])
	{	
		if (map->floor_color)
			return (error_duplicate_color_id(map, i, "F"));
		map->floor_color = ft_strdup(line + j);
		return (1);
	}
	if (line[0] == 'C' && line[j])
	{
		if (map->ceiling_color)
			return (error_duplicate_color_id(map, i, "C"));
		map->ceiling_color = ft_strdup(line + j);
		return (1);
	}
	return (0);
}
