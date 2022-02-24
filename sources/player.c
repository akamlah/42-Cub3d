#include "../header/cub3d.h"

/*
*	Allocates memory for player. Scans map and sets indicated spawnpoint and orientation,
*	Saves them and initialises player position to spawnpoint.
*	Sets player spawnpoint to 0 in map after that.
*/
void	init_player(t_vars *vars)
{
	int i, j;

	vars->player = malloc(sizeof(t_player));
	i = 0;
	while (vars->map->nodes[i] && i < vars->map->n_lines)
	{
		j = 0;
		while (vars->map->nodes[i][j] && vars->map->nodes[i][j] != '\n')
		{
			if (ft_isalpha(vars->map->nodes[i][j]))
			{
				// not sure yet if initial spawnpoint storing is necessary, 
				// would be cool feature as checkpoint in game to return there.
				vars->player->RW_xspawn = j * RW_UNIT + RW_UNIT / 2;
				vars->player->RW_yspawn = i * RW_UNIT + RW_UNIT / 2;
				vars->player->RW_x = vars->player->RW_xspawn;
				vars->player->RW_y = vars->player->RW_yspawn;
				if (vars->map->nodes[i][j] == 'N')
					vars->player->th_spawn = M_PI_2;
				if (vars->map->nodes[i][j] == 'S')
					vars->player->th_spawn = 3 * M_PI_2;
				if (vars->map->nodes[i][j] == 'E')
					vars->player->th_spawn = 0;
				if (vars->map->nodes[i][j] == 'W')
					vars->player->th_spawn = M_PI;
				vars->player->th = vars->player->th_spawn;
				vars->map->nodes[i][j] = '0';
				break ;
			}
			j++;
		}
		i++;
	}
}
