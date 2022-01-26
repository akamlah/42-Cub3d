#include "../header/cub3d.h"


/*
	The map must be composed of only 6 possible characters: 0 for an empty space,
	1 for a wall, and N,S,E or W for the player’s start position and spawning
	orientation.

	The map must be closed/surrounded by walls, if not the program must return
	an error.

	Except for the map content, each type of element can be separated by one or
	more empty line(s).

	Except for the map content which always has to be the last, each type of
	element can be set in any order in the file.

	Except for the map, each type of information from an element can be separated
	by one or more space(s).

	Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each
	object in a strict order such as :
	∗ North texture:
	NO ./path_to_the_north_texture
	· identifier: NO
	· path to the north texure
	∗ South texture:
	SO ./path_to_the_south_texture
	· identifier: SO
	· path to the south texure
	∗ West texture:
	WE ./path_to_the_west_texture
	· identifier: WE
	· path to the west texure
	∗ East texture:
	EA ./path_to_the_east_texture
	· identifier: EA
	· path to the east texure
	∗ Floor color:
	F 220,100,0
	· identifier: F
	· R,G,B colors in range [0,255]: 0, 255, 255
	∗ Ceilling color:
	C 225,30,0
	· identifier: C
	· R,G,B colors in range [0,255]: 0, 255, 255
	If any misconfiguration of any kind is encountered in the file, the program
	must exit properly and return "Error\n" followed by an explicit error message
	of your choice.
*/

// exit from main but error msgs printed by subfunctions

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
		return(0);
	}
	return (1);
}

void	map_init(t_map *map)
{
	map->fd_cubfile = 0;
	map->nodes = NULL;
	map->textr_n = NULL;
	map->textr_s = NULL;
	map->textr_w = NULL;
	map->textr_e = NULL;
	map->floor_color = NULL;
	map->ceiling_color = NULL;
	// ...
}

// parses line by line
int	parse_line(char *tmp, int i, t_map *map)
{
	char *line;

	line = ft_strtrim(tmp, "\n");
		free(tmp);
	if (is_map_chars(line) && !is_whitespaces(line))
	{
		free(line);
		return (only_map_after(map, i));
	}
	else if (get_texture(line, map, i))
		free(line);
	else if (get_color_id(line, map))
		free(line);
	else if (is_whitespaces(line))
		free(line);
	else
	{
		printf("Error\nLine %d: invalid identifier\n", i + 1);
		print_usage_message(2);
		free(line);
		return (1);
	}
	return (0);
}

// main parser
int	parse(t_vars *vars, int argc, char **argv)
{
	t_map	*map;
	int		i;
	char	*tmp;

	map = malloc(sizeof(t_map));
	vars->map = map;
	map_init(map);
	if (argc != 2)
	{
		print_usage_message(1);
		return (1);
	}
	if (!open_cubfile(map, argv[1]))
		return (1);
	i = 0;
	while (1)
	{
		tmp = get_next_line(map->fd_cubfile);
		if (!tmp)
			break ;
		if (parse_line(tmp, i, map))
			return (1);
		i++;
	}
	return (0);
}
