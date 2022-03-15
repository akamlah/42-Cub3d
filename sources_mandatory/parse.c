/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:32:23 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/14 21:54:47 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_mandatory/cub3d_mandatory.h"

int	open_cubfile(t_map *map, char *path)
{
	char	*extension;
	int		path_len;

	path_len = ft_strlen(path);
	map->fd_cubfile = open(path, O_RDONLY);
	if (map->fd_cubfile < 0)
	{
		printf("Error\n");
		perror(path);
		print_usage_message(1);
		return (0);
	}
	extension = ft_strchr_rev(path, '.');
	if (!extension || path_len < 4)
	{
		printf("Errror\nWrong file format, must be .cub\n");
		return (0);
	}
	if (ft_strncmp(extension, ".cub", 4))
	{
		printf("Errror\nWrong file format, must be .cub\n");
		return (0);
	}
	return (1);
}

static void	map_init(t_map *map)
{
	map->fd_cubfile = 0;
	map->subf_error = 0;
	map->startline = 0;
	map->n_lines = 0;
	map->max_width = 0;
	map->path = NULL;
	map->nodes = NULL;
	map->textr_n = NULL;
	map->textr_s = NULL;
	map->textr_w = NULL;
	map->textr_e = NULL;
	map->floor_color = NULL;
	map->ceiling_color = NULL;
}

static int	got_all_data(t_vars *vars)
{
	if (!vars->map->ceiling_color || !vars->map->floor_color
		|| !vars->map->textr_w || !vars->map->textr_e
		|| !vars->map->textr_n || !vars->map->textr_s)
	{
		printf("Error\n");
		if (!vars->map->ceiling_color)
			printf("Missing color identifier for ceiling\n");
		if (!vars->map->floor_color)
			printf("Missing color identifier for floor\n");
		if (!vars->map->textr_s)
			printf("Missing texture for south\n");
		if (!vars->map->textr_n)
			printf("Missing texture for north\n");
		if (!vars->map->textr_e)
			printf("Missing texture for east\n");
		if (!vars->map->textr_w)
			printf("Missing texture for west\n");
		print_usage_message(2);
		return (0);
	}
	return (1);
}

/*
	Goes through whole .cub file fline by line and checks the format
*/
static int	parse_line(char *tmp, int i, t_vars *vars)
{
	char	*line;

	line = ft_strtrim(tmp, "\n");
	free(tmp);
	if (!get_texture(line, vars->map, i)
		&& !get_color_id(line, vars->map, i)
		&& !is_whitespaces(line)
		&& !get_map(line, vars->map, i))
	{
		if (!vars->map->subf_error)
		{
			printf("Error\nLine |%s| %d: invalid identifier\n", line, i + 1);
			print_usage_message(2);
		}
		free(line);
		return (1);
	}
	free(line);
	return (0);
}

/*
	MAIN PARSER
*/
int	parse(t_vars *vars, char **argv)
{
	t_map	*map;
	int		i;
	char	*tmp;

	map = malloc(sizeof(t_map));
	vars->map = map;
	map_init(map);
	map->path = argv[1];
	if (!open_cubfile(map, map->path))
		return (1);
	i = 0;
	while (1)
	{
		tmp = get_next_line(map->fd_cubfile);
		if (!tmp)
			break ;
		if (parse_line(tmp, i, vars))
			return (1);
		i++;
	}
	close (vars->map->fd_cubfile);
	if (!got_all_data(vars))
		return (1);
	return (parse_map_lines(vars));
}
