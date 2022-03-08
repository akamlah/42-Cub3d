#include "../header/cub3d.h"

static int	set_fd(t_vars *vars)
{
	int	fd;

	if (vars->map->max_width < 3 || vars->map->n_lines < 3)
	{
		printf("Error\nInvaliid map size!\n");
		return (0);
	}
	fd = open(vars->map->path, O_RDONLY);
	if (fd < 0)
		return (0);
	return (fd);
}

static char	**linebuff_error(int i, int *fd, char ***maplines)
{
	printf("reached end of file %d\n", i);
	free(*maplines);
	close(*fd);
	return (NULL);
}

static void	dup_linebuff(char ***maplines, char **linebuff, int *linecount)
{
	int	i;

	(*maplines)[*linecount] = ft_strdup(*linebuff);
	*linecount += 1;
	i = *linecount;
}

static char	**get_map_lines(t_vars *vars)
{
	int		fd;
	int		i;
	int		linecount;
	char	*linebuff;
	char	**maplines;

	maplines = NULL;
	fd = set_fd(vars);
	i = 0;
	linecount = 0;
	maplines = malloc((vars->map->max_width + 2) * (vars->map->n_lines + 2));
	while (i < vars->map->startline + vars->map->n_lines - 1)
	{
		linebuff = get_next_line(fd);
		if (!linebuff)
			return (linebuff_error(i, &fd, &maplines));
		if (i >= vars->map->startline - 1)
			dup_linebuff(&maplines, &linebuff, &linecount);
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
	if (check_borders(vars, maplines)
		|| check_map(vars, maplines))
		return (1);
	vars->map->nodes = maplines;
	return (0);
}
