#include "../header/cub3d.h"

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
			return (1);
		printf("Error\nMap: Line %d: Invalid sequence\n\
		\b\b\b\b\b\b\b\b- Map can contain only: '0', '1', 'N', 'W', 'S', 'E' or space,\n\
		\b\b\b\b\b\b\b\b- should be the last element in a .cub file'\n\
		\b\b\b\b\b\b\b\b- should not be interrupted by other lines or newlines.\n",\
		line_err + 1);
		map->subf_error = 1;
		return (0);
	}
	return (0);
}