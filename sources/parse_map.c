#include "../header/cub3d.h"



int	check_char(t_vars *vars, char **maplines, int x, int y)
{
	if (maplines[y][x] == ' ' && !check_emptyspace(vars, maplines, x, y))
		return (0);
	return (1);
}

char	**get_map_lines(t_vars *vars)
{
	int		fd;
	int		i;
	int		linecount;
	char	*linebuff;
	char	**maplines = NULL;

	i = 0;
	linecount = 0;
	fd = open(vars->map->path, O_RDONLY);
	if (fd < 0)
		return (0);
	maplines = malloc((vars->map->max_width + 1) * (vars->map->n_lines + 1));
	while (i < vars->map->startline + vars->map->n_lines - 1)
	{
		linebuff = get_next_line(fd);
		if (!linebuff)
		{
			printf("reached end of file %d\n", i);
			free(maplines);
			close(fd);
			return (0);
		}
		if (i >= vars->map->startline - 1)
		{
			maplines[linecount] = ft_strdup(linebuff);
			linecount++;
		}
		free(linebuff);
		i++;
	}
	close (fd);
	maplines[linecount] = NULL;
	return (maplines);
}

int	parse_map_lines(t_vars *vars)
{
	int		x;
	int		y;
	char	**maplines;

	x = 0;
	y = 0;
	maplines = get_map_lines(vars);
	if (!maplines)
		return (1);
	while (maplines[y])
	{
		while (maplines[y][x])
		{
			if (!check_char(vars, maplines, x, y))
				return (1);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
