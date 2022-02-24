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
// win_ptr size (WW width, WH heigth in pixel)
// https://support.microsoft.com/en-us/windows/getting-the-best-display-on-your-monitor-c7e01f63-9b51-2b23-0a0f-6b965af015a9
// # define WW 1920
// # define WH 1080
# define WW 1200
# define WH 800

// defines how big a cube is in the 2D abstraction,
// (this is just the abstract pace in the 2D grid, not pixels!)
# define RW_UNIT 64

// field of view (angle, in rad)
# define FOV (M_PI / 3)

// width  and height of projection plane
# define PRJP_W 320
# define PRJP_H 200

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
	char	*path;

	// final matrix filled:
	char	**nodes;

	// new mapdata:
	int		startline;
	int		n_lines;
	int		max_width;

	int		subf_error;

	char	*textr_n;
	char	*textr_s;
	char	*textr_w;
	char	*textr_e;
	char	*ceiling_color;
	char	*floor_color;

}			t_map;

typedef struct	s_image
{
	void	*img_ptr;
	char	*address;
	int		width;
	int		height;
	int		S_xtlc;
	int		S_ytlc;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct mlx_vars
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_mlx_vars;

<<<<<<< Updated upstream

typedef struct s_player
{

	double	orientation;
	// player  data - have better names and struct?
	int	px; // player x screen coord topdown
	int	py; // player y screen coord topdown
	int	size; // player size (square) . justt 4 tests 

}	t_player;

=======
typedef struct s_player
{
	int		RW_xspawn;
	int		RW_yspawn;
	float	th_spawn;
	int		RW_x;
	int		RW_y;
	float	th;
}				t_player;

typedef struct s_minimap
{
	t_image	*img;
	int		scale;
	int		width;
	int		height;

	// not used yet/;
	char	wall_color;
	char	floor_color;
	char	background_color;
}				t_minimap;
>>>>>>> Stashed changes
typedef struct s_vars
{
	//andi
	t_mlx_vars *mlx_vars;

	//alice
<<<<<<< Updated upstream
	t_map	*map;

	// struct minimap? 
	int	minimap_scale;
	int	minimap_xwinoffset;
	int	minimap_ywinoffset;
	int	minimap_xframelen;
	int minimap_yframelen;
	int	minimap_xframeoffset;
	int	minimap_yframeoffset;

	t_player *player;

	int scale;

=======
	t_map		*map;
	t_player	*player;
	t_minimap	*minimap;
	t_image		*prjp;
>>>>>>> Stashed changes
}	t_vars;


// FUNCTIONS
//Andi
int		init_mlx_vars(t_vars *vars);
int		mlx_hooks(t_vars *vars);
int		exit_hook(t_vars *vars);
int		update(t_vars *vars);
void	*loadimage(char *path, t_vars *vars);
int		parse_map_lines(t_vars *vars);
int		check_map(t_vars *vars, char	**maplines);
int		check_borders(t_vars *vars, char **maplines);

// Alice
int		parse(t_vars *vars, int argc, char **argv);
int		is_whitespaces(char *line);
int		get_texture(char *line, t_map *map, int i);
int		get_color_id(char *line, t_map *map, int i);
int		get_map(char *line, t_map *map, int i);
void	free_and_exit(t_vars *vars);
int		open_cubfile(t_map *map, char *path);

int		cub_dealkey(int keycode, t_vars *vars);

void	init_player(t_vars *vars);
void	init_minimap(t_vars *vars);
void	draw_minimap(t_vars *vars);
void	draw_player_minimap(t_vars *vars);

void	draw_all(t_vars *vars);

// utils:
int		cub_pixel_put(t_image *img, int x, int y, int color);
t_image	*new_image(t_vars *vars, int width, int height, int S_xtlc, int S_ytlc);
void	draw_square_tlc(t_image *img, int width, int height, int I_xtlc, int I_ytlc, int color);

# endif