#include "../header_bonus/cub3d_bonus.h"

/*
	checks if a character is a spawn indicator
*/
int	is_valid_c(char c)
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

/*
	checks if a string is a map line
	spaces okay 
*/
static int	is_map_chars(char	*line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] > MAX_OBJ_CHAR && ft_isdigit(line[i])
			&& line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'E'
			&& line[i] != '\n')
			return (0);
		i++;
	}
	if (i > map->max_width)
		map->max_width = i;
	return (1);
}

/*
	Checks wether the lines after the first map line contain only allowed
	characters and whitespaces or not.
*/
static int	only_maplines_after(t_map *map, int i)
{
	char	*line;

	i++;
	while (1)
	{
		line = get_next_line(map->fd_cubfile);
		if (!line)
		{
			map->n_lines = i - map->startline + 1;
			return (0);
		}
		if (!(!is_whitespaces(line) && is_map_chars(line, map)))
		{
			free(line);
			return (i);
		}
		free(line);
		i++;
	}
	return (0);
}

int	get_map(char *line, t_map *map, int i)
{
	int	line_err;

	map->startline = i + 1;
	if (!is_whitespaces(line) && is_map_chars(line, map))
	{
		line_err = only_maplines_after(map, i);
		if (!line_err)
			return (1);
		printf("Error\nMap: Line %d: Invalid sequence\n", line_err + 1);
		printf("\tMap can contain only: '0', '1', 'N', 'W', 'S', 'E' or space\n");
		printf("\tMap should be the last element in a `.cub' file\n");
		printf("\tMap should not be interrupted by other lines or newlines\n");
		map->subf_error = 1;
		return (0);
	}
	return (0);
}
