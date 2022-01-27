#include "../header/cub3d.h"

int	parse_map(t_map *map)
{
	if (!open_cubfile(map, map->path))
		return (1);
	return (0);
}

/*
	checks if a string is a map line
	spaces okay 
*/
int	is_map_chars(char	*line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
		&& line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E'
		&& line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

// only map or just whitespaces
int	only_maplines_after(t_map *map, int i)
{
	char *line;
	
	i++;
	while (1)
	{
		line = get_next_line(map->fd_cubfile);
		if (!line)
			return (0);
		if (!(!is_whitespaces(line) && is_map_chars(line)))
		{
			printf("this ine %s\n", line);
			free(line);
			return (i);
		}
		free(line);
		i++;
	}
	return (0);
}

int get_map(char *line, t_map *map, int i)
{
	int	line_err;
	if (!is_whitespaces(line) && is_map_chars(line))
	{
		line_err = only_maplines_after(map, i);
		if (!line_err)
		{
			//close(map->fd_cubfile);
			//map->fd_cubfile = 0;
			//parse_map(map);
			return (1);
		}
		printf("Error\nMap: Line %d: Invalid sequence\n", line_err + 1);
		printf("\tMap can contain only: '0', '1', 'N', 'W', 'S', 'E' or space\n");
		printf("\tMap should be the last element in a `.cub' file\n");
		printf("\tMap should not be interrupted by other lines or newlines\n");
		map->subf_error = 1;
		return (0);
	}
	return (0);
}
