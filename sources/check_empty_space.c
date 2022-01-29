#include "../header/cub3d.h"

int	check_empty_top(char **maplines, int x, int y)
{
	int	length_top;
	int	length_middle;

	if (y == 0)
		return (0);
	length_top = (int)ft_strlen(maplines[y - 1]);
	length_middle = (int)ft_strlen(maplines[y]);
	if(( length_top >= length_middle && maplines[y - 1][x] != '1' && maplines[y - 1][x] != ' ')
		|| (length_top >= length_middle - 1 && x != 0 && maplines[y - 1][x - 1] != '1' && maplines[y - 1][x - 1] != ' ') 
		|| (length_top >= length_middle + 1 && x + 1 < length_top && maplines[y - 1][x + 1] != '1'
			&& maplines[y - 1][x + 1] != ' ')) 
		return (1);
	else
		return (0);
}

int	check_empty_bot(t_vars *vars, char **maplines, int x, int y)
{
	int	length_bot;
	int	length_middle;

	if (y == vars->map->n_lines - 1)
		return (0);
	length_bot = (int)ft_strlen(maplines[y + 1]);
	length_middle = (int)ft_strlen(maplines[y]);
	if((maplines[y + 1][x] != '1' && maplines[y + 1][x] != ' ') // one to bottom
		|| (x != 0 && maplines[y + 1][x - 1] != '1' && maplines[y + 1][x - 1] != ' ') //bottom-left corner
		|| (x + 1 < length_middle && maplines[y + 1][x + 1] != '1' && maplines[y + 1][x + 1] != ' ')) //bottom-right corner
		return (1);
	else
		return (0);
}

int	check_empty_lr(char **maplines, int x, int y)
{
	if((x != 0 && maplines[y][x - 1] != '1' && maplines[y][x - 1] != ' ') 	//one to left
		|| (x + 1 < (int)ft_strlen(maplines[y]) && maplines[y][x + 1] != '1' && maplines[y][x + 1] != ' ')) // one to right
		return (1);
	else
		return (0);
}

int	check_emptyspace(t_vars *vars, char	**maplines, int x, int y)
{
	if (check_empty_bot(vars, maplines, x, y) || check_empty_top(maplines, x, y) || check_empty_lr(maplines, x, y))
		{
			printf("Error: Map: Empty Character at (x: %d, y: %d) not enclosed by walls\n", x, y);
			return (0);
		}
	return (1);
}
