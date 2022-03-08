#include "../header/cub3d.h"

int	check_top(char **maplines, t_vector2_int pos, char checkchar)
{
	int	length_top;
	int	length_middle;

	if (pos.y == 0)
		return (0);
	length_top = (int)ft_strlen(maplines[pos.y - 1]);
	length_middle = (int)ft_strlen(maplines[pos.y]);
	if (length_top - 3 < pos.x)
		return (1);
	if ((length_top >= length_middle \
		&& maplines[pos.y - 1][pos.x] != '1' \
		&& maplines[pos.y - 1][pos.x] != checkchar \
		&& !is_valid_c(maplines[pos.y - 1][pos.x])) \
		|| (length_top >= length_middle - 1 && pos.x != 0 \
		&& maplines[pos.y - 1][pos.x - 1] != '1' \
		&& maplines[pos.y - 1][pos.x - 1] != checkchar \
		&& !is_valid_c(maplines[pos.y - 1][pos.x - 1])) \
		|| (length_top >= length_middle + 1 && pos.x + 1 < length_top \
		&& maplines[pos.y - 1][pos.x + 1] != '1' \
		&& maplines[pos.y - 1][pos.x + 1] != checkchar \
		&& !is_valid_c(maplines[pos.y - 1][pos.x + 1])))
		return (1);
	else
		return (0);
}

int	check_bot(t_vars *vars, char **maplines, t_vector2_int pos, char checkchar)
{
	int	length_bot;
	int	length_middle;

	if (pos.y == vars->map->n_lines - 1)
		return (0);
	length_bot = (int)ft_strlen(maplines[pos.y + 1]);
	length_middle = (int)ft_strlen(maplines[pos.y]);
	if (length_bot - 2 < pos.x)
		return (1);
	if ((length_bot >= length_middle && maplines[pos.y + 1][pos.x] != '1' \
		&& (maplines[pos.y + 1][pos.x] != checkchar) \
		&& !is_valid_c(maplines[pos.y + 1][pos.x])) \
		|| (length_bot >= length_middle - 1 && pos.x != 0 \
		&& maplines[pos.y + 1][pos.x - 1] != '1' \
		&& maplines[pos.y + 1][pos.x - 1] != checkchar \
		&& !is_valid_c(maplines[pos.y + 1][pos.x - 1])) \
		|| (length_bot >= length_middle + 1 && pos.x + 1 < length_middle \
		&& maplines[pos.y + 1][pos.x + 1] != '1' \
		&& maplines[pos.y + 1][pos.x + 1] != checkchar \
		&& !is_valid_c(maplines[pos.y + 1][pos.x + 1])))
		return (1);
	else
		return (0);
}

int	check_lr(char **maplines, t_vector2_int pos, char checkchar)
{
	int	length_middle;

	length_middle = (int)ft_strlen(maplines[pos.y]);
	if ((pos.x != 0 \
		&& maplines[pos.y][pos.x - 1] != '1' \
		&& maplines[pos.y][pos.x - 1] != checkchar \
		&& !is_valid_c(maplines[pos.y][pos.x - 1])) \
		|| ((pos.x + 1 < length_middle
		&& maplines[pos.y][pos.x + 1] != '1' \
		&& maplines[pos.y][pos.x + 1] != checkchar) \
		&& pos.x < length_middle - 2 \
		&& !is_valid_c(maplines[pos.y][pos.x + 1])))
		return (1);
	else
		return (0);
}

//Checks with spaces
int	check_top_space(char **maplines, t_vector2_int pos)
{
	int	length_top;
	int	length_middle;

	if (pos.y == 0)
		return (0);
	length_top = (int)ft_strlen(maplines[pos.y - 1]);
	length_middle = (int)ft_strlen(maplines[pos.y]);
	if (length_top - 3 < pos.x)
		return (1);
	if ((length_top >= length_middle \
		&& maplines[pos.y - 1][pos.x] != '1' \
		&& maplines[pos.y - 1][pos.x] != ' ') \
		|| (length_top >= length_middle - 1 && pos.x != 0 \
		&& maplines[pos.y - 1][pos.x - 1] != '1' \
		&& maplines[pos.y - 1][pos.x - 1] != ' ') \
		|| (length_top >= length_middle + 1 && pos.x + 1 < length_top \
		&& maplines[pos.y - 1][pos.x + 1] != '1' \
		&& maplines[pos.y - 1][pos.x + 1] != ' '))
		return (1);
	else
		return (0);
}

int	check_bot_space(t_vars *vars, char **maplines, t_vector2_int pos)
{
	int	length_bot;
	int	length_middle;

	if (pos.y == vars->map->n_lines - 1)
		return (0);
	length_bot = (int)ft_strlen(maplines[pos.y + 1]);
	length_middle = (int)ft_strlen(maplines[pos.y]);
	if (length_bot - 2 < pos.x)
		return (1);
	if ((length_bot >= length_middle && maplines[pos.y + 1][pos.x] != '1' \
		&& (maplines[pos.y + 1][pos.x] != ' ')) \
		|| (length_bot >= length_middle - 1 && pos.x != 0 \
		&& maplines[pos.y + 1][pos.x - 1] != '1' \
		&& maplines[pos.y + 1][pos.x - 1] != ' ') \
		|| (length_bot >= length_middle + 1 && pos.x + 1 < length_middle \
		&& maplines[pos.y + 1][pos.x + 1] != '1' \
		&& maplines[pos.y + 1][pos.x + 1] != ' '))
		return (1);
	else
		return (0);
}
