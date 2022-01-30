#include "../header/cub3d.h"

int	check_top_bot(t_vars *vars, char **maplines)
{
	int	y;
	int x;

	y = vars->map->n_lines - 1;
	x = 0;
	while (maplines[0][x] && x < (int)ft_strlen(maplines[0]) - 2)
	{
		if (maplines[0][x] != '1' && maplines[0][x] != ' ')
		{
			printf("Error: Map: Map not inclosed in walls (x: %d, y: %d\n", x, 0);
			return (1);
		}
		x++;
	}
	x = 0;
	while (maplines[y][x] && x < (int)ft_strlen(maplines[y]) - 2)
	{
		if (maplines[y][x] != '1' && maplines[y][x] != ' ')
		{
			printf("Error: Map: Map not inclosed in walls (x: %d, y: %d\n", x, y);
			return (1);
		}
		x++;
	}
	return (0);
}

int	check_front(char **maplines, int y)
{
	int	x;

	x = 0;
	while (maplines[y][x] && maplines[y][x] == ' ')
			x++;
	if (maplines[y][x] != '1')
	{
		printf("Error: Map: Map not inclosed in walls (x: %d, y: %d\n", x, y);
		return (1);
	}
	return (0);
}

int	check_back(char **maplines, int y)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = (int)ft_strlen(maplines[y]);
	while (maplines[y][line_len - 2 - i] && maplines[y][line_len - 2 - i] == ' ')
			i++;
	if (maplines[y][line_len - 2 - i] != '1')
	{
		printf("Error: Map: Map not inclosed in walls (x: %d, y: %d\n", line_len - 2 - i, y);
		return (1);
	}
	return (0);
}

int	check_borders(t_vars *vars, char **maplines)
{
	int	y;

	y = 0;
	while (maplines[y])
	{
		if (check_front(maplines, y)
			|| check_back(maplines, y))
			return (1);
		y++;
	}
	if (check_top_bot(vars, maplines))
		return (1);
	return (0);
}

int	check_char(t_vars *vars, char **maplines, int x, int y)
{
	if ((maplines[y][x] == ' ' || maplines[y][x] == '0') && !check_map_squares(vars, maplines, x, y))
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
	if (check_borders(vars, maplines))
	{
		return (1);
	}
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
