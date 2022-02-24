#include "../header/cub3d.h"

/*
*	Set all pointers in main struct to null or allocate memory for them before using them
*/
void	vars_init(t_vars *vars)
{
	vars->map = NULL;
	vars->mlx_vars = NULL;
	vars->player = NULL;
	vars->prjp = NULL;
	vars->minimap = malloc(sizeof(t_minimap));
	vars->minimap->img = NULL;
}

int main(int argc, char **argv)
{
	t_vars	vars;
	int		error;

	vars_init(&vars);
	error = parse(&vars, argc, argv);
	if (error)
		free_and_exit(&vars);

	init_mlx_vars(&vars);
	init_player(&vars);


	draw_all(&vars);
	mlx_hooks(&vars);
	return (0);
}

/*
*	ONLY EXITPOINT here.
*	Checks for any variable to be freed.
*/
void	free_and_exit(t_vars *vars)
{
	// free map vars:
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
		free(vars->map);
	}

	// free mlx vars:
	if (vars->mlx_vars)
		free(vars->mlx_vars);
	
	// player vars:
	if (vars->player)
		free(vars->player);

	// minimap vars:
	if (vars->minimap)
	{
		if (vars->minimap->img)
			free(vars->minimap->img);
		free(vars->minimap);
	}

	// system("leaks cub3D");
	exit(0);
}
