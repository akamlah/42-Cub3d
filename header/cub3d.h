#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"


// screen parameters
// window size (WW width, WH heigth in pixel)
# define WW 2560
# define WH 1600

//keycodes
# define key_left 123
# define key_right 124
# define key_up 126
# define key_down 125
# define key_a 0
# define key_d 2
# define key_w 13
# define key_s 1

# define key_esc 53

typedef struct s_point
{
	int		x;
	int		y;
	int		wall;
	char	spawn_or;
}			t_point;

typedef struct s_map
{
	int		fd_cubfile;
	int		subf_error;
	int		eof;
	t_point	**nodes;
	char	*textr_n;
	char	*textr_s;
	char	*textr_w;
	char	*textr_e;
	char	*ceiling_color;
	char	*floor_color;
}			t_map;

typedef struct mlx_vars
{
	void *mlx;
	void *window;
	void *mainImg;
}			t_mlx_vars;

typedef struct s_vars
{
	//andi
	t_mlx_vars *mlx_vars;


	//alice
	t_map	*map;

}	t_vars;

// FUNCTIONS
//Andi

int	init_mlx_vars(t_vars *vars);
int	mlx_hooks(t_vars *vars);
int exit_hook(t_vars *vars);
int	update(t_vars *vars);
int	key_hook(int keycode, t_vars *vars);

// Alice
int	parse(t_vars *vars, int argc, char **argv);
int	is_whitespaces(char *line);
int	get_texture(char *line, t_map *map, int i);
int	get_color_id(char *line, t_map *map, int i);
int	get_map(char *line, t_map *map, int i);
void	exit_cub(t_vars *vars);



# endif