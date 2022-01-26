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


int	only_map_after(t_map *map, int i)
{
	char *line;
	
	i++;
	while (1)
	{
		line = get_next_line(map->fd_cubfile);
		if (!line)
			break ;
		if (!(is_map_chars(line) && !is_whitespaces(line)))
		{
			free(line);
			return (1);
		}
		free(line);
		i++;
	}
	return (0);
}