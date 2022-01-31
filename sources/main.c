#include "../header/cub3d.h"

// only exitpoint, easier check for leaks
void	exit_cub(t_vars *vars)
{
	// eventually call freeing functions?

	if (vars->map)
	{
		if (vars->map->fd_cubfile)
			close(vars->map->fd_cubfile);
		if (vars->map->textr_n)
			free(vars->map->textr_n);
		if (vars->map->textr_s)
			free(vars->map->textr_s);
		if (vars->map->textr_w)
			free(vars->map->textr_w);
		if (vars->map->textr_e)
			free(vars->map->textr_e);
		if (vars->map->floor_color)
			free(vars->map->floor_color);
		if (vars->map->ceiling_color)
			free(vars->map->ceiling_color);
	// if (vars->mlx_vars->minimap)
	// 	free(vars->mlx_vars->minimap);
		free(vars->map);
	}
	// system("leaks cub3D");
	exit(0);
}

void	vars_init(t_vars *vars)
{
	vars->map = NULL;
	vars->minimap_scale = 20;
	vars->mlx_vars->minimap = NULL;
	// set to spawn stuff when parsing
	vars->player = malloc(sizeof(t_player));
	vars->player->px = 0;
	vars->player->py = 0;
	vars->player->size = 4;
	vars->player->orientation = 0;
	
	vars->scale = 50;
	// ...
}

/*
*HELLO
*/
int main(int argc, char **argv)
{
	t_vars	vars;

	vars_init(&vars);
	if (parse(&vars, argc, argv))
	{
		exit_cub(&vars);
	}

		//--------------------------------
		// check parsing:
		printf("tn |%s|\n", vars.map->textr_n);
		printf("ts |%s|\n", vars.map->textr_s);
		printf("tw |%s|\n", vars.map->textr_w);
		printf("te |%s|\n", vars.map->textr_e);
		printf("f |%s|\n", vars.map->floor_color);
		printf("c |%s|\n", vars.map->ceiling_color);
		printf("map startline %d\n", vars.map->startline);
		printf("map height %d\n", vars.map->n_lines);
		printf("map width %d\n", vars.map->max_width);

		int i, j;
		i = 0;
		while (vars.map->nodes[i] && i < vars.map->n_lines)
		{
			j = 0;
			while (vars.map->nodes[i][j] && vars.map->nodes[i][j] != '\n')
			{
				printf("%c", vars.map->nodes[i][j]);
				j++;
			}
			// printf("\n");
			i++;
		}
		//--------------------------------

	init_mlx_vars(&vars);




	compone_window(&vars);

	mlx_hooks(&vars);
	
	return (0);
}
