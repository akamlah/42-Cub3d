#include "../header/cub3d.h"

void	print_usage_message(int msg)
{
	if (msg == 1)
		printf("Usage:\t./cub3D <path to `.cub' file>\n");
	if (msg == 2)
		printf("Valid identifiers:\n\
		NO ./path_to_the_north_texture\n\
		SO ./path_to_the_south_texture\n\
		WE ./path_to_the_west_texture\n\
		EA ./path_to_the_east_texture\n\
		F [floor color R,G,B]\n\
		C [ceiling color R,G,B]\n\
		or lines of the map\n");
}

int	open_cubfile(t_map *map, char *path)
{
	map->fd_cubfile = open(path, O_RDONLY);
	if (map->fd_cubfile < 0)
	{
		perror(path);
		print_usage_message(1);
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
	return (parse_map_lines(vars));
}
