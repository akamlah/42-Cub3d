#include "../header/cub3d.h"

int	is_valid_c(char c)
{
	char *valid_c;
	int	i;

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

int	check_top(char **maplines, int x, int y, char checkchar)
{
	int	length_top;
	int	length_middle;

	if (y == 0)
		return (0);
	length_top = (int)ft_strlen(maplines[y - 1]);
	length_middle = (int)ft_strlen(maplines[y]);
	if (length_top - 3 < x)
		return (1);
	if(( length_top >= length_middle && maplines[y - 1][x] != '1' && maplines[y - 1][x] != checkchar && !is_valid_c(maplines[y - 1][x]))
		|| (length_top >= length_middle - 1 && x != 0 && maplines[y - 1][x - 1] != '1' && maplines[y - 1][x - 1] != checkchar && !is_valid_c(maplines[y - 1][x - 1])) 
		|| (length_top >= length_middle + 1 && x + 1 < length_top && maplines[y - 1][x + 1] != '1'
			&& maplines[y - 1][x + 1] != checkchar && !is_valid_c(maplines[y - 1][x + 1]))) 
		return (1);
	else
		return (0);
}

int	check_bot(t_vars *vars, char **maplines, int x, int y, char checkchar)
{
	int	length_bot;
	int	length_middle;

	if (y == vars->map->n_lines - 1)
		return (0);
	length_bot = (int)ft_strlen(maplines[y + 1]);
	length_middle = (int)ft_strlen(maplines[y]);
	if (length_bot - 3 < x)
		return (1);
	if((length_bot >= length_middle && maplines[y + 1][x] != '1' && (maplines[y + 1][x] != checkchar) && !is_valid_c(maplines[y + 1][x])) // one to bottom
		|| (length_bot >= length_middle - 1 && x != 0 && maplines[y + 1][x - 1] != '1' && maplines[y + 1][x - 1] != checkchar && !is_valid_c(maplines[y + 1][x - 1])) //bottom-left corner
		|| (length_bot >= length_middle + 1 && x + 1 < length_middle && maplines[y + 1][x + 1] != '1' && maplines[y + 1][x + 1] != checkchar && !is_valid_c(maplines[y + 1][x + 1]))) //bottom-right corner
		return (1);
	else
		return (0);
}

int	check_lr(char **maplines, int x, int y, char checkchar)
{
	int	length_middle;

	length_middle = (int)ft_strlen(maplines[y]);
	if((x != 0 && maplines[y][x - 1] != '1' && maplines[y][x - 1] != checkchar && !is_valid_c(maplines[y][x - 1]))	//one to left
		|| ((x + 1 < length_middle && maplines[y][x + 1] != '1' && maplines[y][x + 1] != checkchar) && x < length_middle - 2 && !is_valid_c(maplines[y][x + 1]))) // one to right
		return (1);
	else
		return (0);
}

int	check_square(t_vars *vars, char **maplines, int x, int y)
{
	if ((maplines[y][x] == ' '
		&& (check_bot(vars, maplines, x, y, ' ') || check_top(maplines, x, y, ' ') || check_lr(maplines, x, y, ' ')))
		||
		((maplines[y][x] == '0' || maplines[y][x] == 'N' || maplines[y][x] == 'S' || maplines[y][x] == 'E' || maplines[y][x] == 'W')
		&& (check_bot(vars, maplines, x, y, '0') || check_top(maplines, x, y, '0') || check_lr(maplines, x, y, '0'))))
	{
		printf("Error: Map: Incorrect format at (x: %d, y: %d) not enclosed by walls\n", x, y);
		return (1);
	}
	return (0);
}

int	check_map(t_vars *vars, char **maplines)
{
	int	y;
	int	x;
	int	spawncnt;

	y = 0;
	x = 0;
	spawncnt = 0;
	while (maplines[y])
	{
		while (maplines[y][x])
		{
			if (is_valid_c(maplines[y][x]))
				spawncnt++;
			 if (check_square(vars, maplines, x, y))
				return (1);
			x++;
		}
		x = 0;
		y++;
	}
	if (spawncnt != 1)
	{
		printf("Error: Map: Incorrect number of spawnpoints, only 1 allowed!\n");
		return (1);
	}
	return (0);
}
