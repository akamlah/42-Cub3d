#include "../header/cub3d.h"

int	check_top(char **maplines, int x, int y)
{
	int	length_top;
	int	length_middle;

	if (y == 0)
		return (0);
	length_top = (int)ft_strlen(maplines[y - 1]);
	length_middle = (int)ft_strlen(maplines[y]);
	if (length_top - 3 < x)
		return (1);
	if(( length_top >= length_middle && maplines[y - 1][x] != '1' && maplines[y - 1][x] != maplines[y][x])
		|| (length_top >= length_middle - 1 && x != 0 && maplines[y - 1][x - 1] != '1' && maplines[y - 1][x - 1] != maplines[y][x]) 
		|| (length_top >= length_middle + 1 && x + 1 < length_top && maplines[y - 1][x + 1] != '1'
			&& maplines[y - 1][x + 1] != maplines[y][x])) 
		return (1);
	else
		return (0);
}

int	check_bot(t_vars *vars, char **maplines, int x, int y)
{
	int	length_bot;
	int	length_middle;

	if (y == vars->map->n_lines - 1)
		return (0);
	length_bot = (int)ft_strlen(maplines[y + 1]);
	length_middle = (int)ft_strlen(maplines[y]);
	if (length_bot - 3 < x)
		return (1);
	if((length_bot >= length_middle && maplines[y + 1][x] != '1' && maplines[y + 1][x] != maplines[y][x]) // one to bottom
		|| (length_bot >= length_middle - 1 && x != 0 && maplines[y + 1][x - 1] != '1' && maplines[y + 1][x - 1] != maplines[y][x]) //bottom-left corner
		|| (length_bot >= length_middle + 1 && x + 1 < length_middle && maplines[y + 1][x + 1] != '1' && maplines[y + 1][x + 1] != maplines[y][x])) //bottom-right corner
		return (1);
	else
		return (0);
}

int	check_lr(char **maplines, int x, int y)
{
	int	length_middle;

	length_middle = (int)ft_strlen(maplines[y]);
	if((x != 0 && maplines[y][x - 1] != '1' && maplines[y][x - 1] != maplines[y][x])	//one to left
		|| ((x + 1 < length_middle && maplines[y][x + 1] != '1' && maplines[y][x + 1] != maplines[y][x]) && x < length_middle - 2)) // one to right
		return (1);
	else
		return (0);
}

int	check_map_squares(t_vars *vars, char	**maplines, int x, int y)
{
	if (check_bot(vars, maplines, x, y) || check_top(maplines, x, y) || check_lr(maplines, x, y))
		{
			printf("Error: Map: Empty Character at (x: %d, y: %d) not enclosed by walls\n", x, y);
			return (0);
		}
	return (1);
}
