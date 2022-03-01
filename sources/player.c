#include "../header/cub3d.h"

/*
*	Allocates memory for player. Scans map and sets indicated spawnpoint and orientation,
*	Saves them and initialises player position to spawnpoint.
*	Sets player spawnpoint to 0 in map after that.
*/
	// not sure yet if initial spawnpoint storing is necessary, 
	// would be cool feature as checkpoint in game to return there.
int	get_player_spawn(t_vars *vars)
{
	int i, j;

	// vars->player = malloc(sizeof(t_player));
	i = 0;
	while (vars->map->nodes[i] && i < vars->map->n_lines)
	{
		j = 0;
		while (vars->map->nodes[i][j] && vars->map->nodes[i][j] != '\n')
		{
			if (ft_isalpha(vars->map->nodes[i][j]))
			{
				vars->player.spawn_pos.x = j * vars->scale + vars->scale / 2;
				vars->player.spawn_pos.y = i * vars->scale + vars->scale / 2;
				vars->player.pos.x = vars->player.spawn_pos.x;
				vars->player.pos.y = vars->player.spawn_pos.y;
				if (vars->map->nodes[i][j] == 'N')
					vars->player.spawn_angle = M_PI_2;
				if (vars->map->nodes[i][j] == 'S')
					vars->player.spawn_angle = 3 * M_PI_2;
				if (vars->map->nodes[i][j] == 'E')
					vars->player.spawn_angle = 0;
				if (vars->map->nodes[i][j] == 'W')
					vars->player.spawn_angle = M_PI;
				vars->player.angle = vars->player.spawn_angle;
				vars->map->nodes[i][j] = '0';
				break ;
			}
			j++;
		}
		i++;
	}
	// vars->player.pos.x = 0;
	// vars->player.pos.y = 0;
	// vars->player.angle = 0;

	// vars->player.speed = 1;
	// vars->player.rot_speed = 0.05;
	// vars->player.move_backward = 0;
	// vars->player.move_forward = 0;
	// vars->player.move_left = 0;
	// vars->player.move_right = 0;
	// vars->player.rotate_left = 0;
	// vars->player.rotate_right = 0;
	// vars->player.fov = 1.04;
	// vars->player.dir.x = 0;
	// vars->player.dir.y = 0;
	
	return (0);
}


// int		**get_player_spawn(t_vars *vars)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (vars->map->nodes[i] && i < vars->map->n_lines)
// 	{
// 		j = 0;
// 		while (vars->map->nodes[i][j] && vars->map->nodes[i][j] != '\n')
// 		{
// 			if (vars->map->nodes[i][j] == 'N')
// 			{
// 				vars->minimap.p_pos.x = j * vars->minimap.scale - vars->minimap.p_size / 2 + vars->minimap.scale * 0.5;
// 				vars->minimap.p_pos.y = i * vars->minimap.scale - vars->minimap.p_size / 2 + vars->minimap.scale * 0.5;
// 				vars->player.pos.x = (double)(j * vars->scale + vars->scale * 0.5);
// 				vars->player.pos.y = (double)(i * vars->scale + vars->scale * 0.5);
// 				vars->player.angle = M_PI * 0.5;
// 				vars->map->nodes[i][j] = '0';
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }