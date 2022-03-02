#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <limits.h>
///////////////////////////REMOVE REMOVE REMOVE RFEMOVE REMOVE REMOVE REMOVE
#include <sys/time.h> ///////////////////////////REMOVE REMOVE REMOVE RFEMOVE REMOVE REMOVE REMOVE
///////////////////////////REMOVE REMOVE REMOVE RFEMOVE REMOVE REMOVE REMOVE

// screen parameters
// win_ptr size (WW width, WH heigth in pixel)
// https://support.microsoft.com/en-us/windows/getting-the-best-display-on-your-monitor-c7e01f63-9b51-2b23-0a0f-6b965af015a9

# define WW 1920
# define WH 1080
// # define WW 2000
// # define WH 800
# define SCALE 64

// width  and height of projection plane
# define MAIN_IMG_W (WW - 40)
# define MAIN_IMG_H (WH - 40)

// field of view (angle, in rad)
# define FOV_DEG 60
# define FOV_RAD (M_PI / 3)

// angular distance between rays when casting within the field of view
// # define RAY_ANG_INCREMENT (2 * (FOV_RAD / MAIN_IMG_W))
# define RAY_ANG_INCREMENT (FOV_RAD / MAIN_IMG_W)
// # define RAY_ANG_INCREMENT (4 * (FOV_RAD / MAIN_IMG_W))

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

typedef struct s_vector2
{
	double		x;
	double		y;
}				t_vector2;

typedef struct s_vector2_int
{
	int		x;
	int		y;
}				t_vector2_int;

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
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_vector2	pos;
	void			*img_ptr;
	char			*address;
	// int		S_xtlc;
	// int		S_ytlc;
}				t_image;

typedef struct	s_ray
{
	t_vector2	hor_hit;
	t_vector2	vert_hit;
	t_vector2	closest_hit;
	int			x_increment_dir;
	int			y_increment_dir;
	double		distance; // use this

	double		angle;
	int			color_minimap;
	double		hor_dx;
	double		hor_dy;
	double		vert_dx;
	double		vert_dy;
	int			facing_direction;
	// double		size_ratio;
	// int			mid_y;
	double	hor_hit_player_dist_RW;
	double	vert_hit_player_dist_RW;

	int			wall_height;
}				t_ray;

typedef struct mlx_vars
{
	void	*mlx_ptr;
	void	*win_ptr;

	t_image		*minimap;

}			t_mlx_vars;
typedef struct s_player
{
	// RENAMED:
	// int		RW_xspawn;
	// int		RW_yspawn;
	// double	th_spawn;
	// int		RW_x;
	// int		RW_y;
	// double	th;

	t_vector2	pos; //actual player position in game world (grid)
	t_vector2	spawn_pos;
	double		spawn_angle;
	double		angle; //player angle

	double		rot_speed;
	double		speed; //player movement speed;

	char		move_forward;
	char		move_backward;
	char		move_left;
	char		move_right;
	char		rotate_left;
	char		rotate_right;
	int			mouse_last_x;
	// double		fov;
	t_vector2	dir;
}				t_player;

typedef struct s_minimap
{
	// t_image	*img; // need to alloc
	int		scale;
	t_vector2	p_pos;

	// not used yet/;
	char	wall_color;
	char	floor_color;
	char	background_color;
	// int			xwinoffset;
	// int			ywinoffset;
	// int			xframelen;
	// int			yframelen;
	// int			xframeoffset;
	// int			yframeoffset;
	// int			p_size;
}				t_minimap;

typedef struct s_vars
{
	
	// int 		scale;
	int			move_forward;

	t_mlx_vars	*mlx_vars;
	t_map		*map;
	t_player	player;
	t_minimap	minimap;
	t_image		*main_img;
	t_image		*tex_N;
	t_image		*tex_S;
	t_image		*tex_E;
	t_image		*tex_W;

	double		last_time_ms;

}	t_vars;


// FUNCTIONS

// parser
int		parse_map_lines(t_vars *vars);
int		check_map(t_vars *vars, char	**maplines);
int		check_borders(t_vars *vars, char **maplines);
int		parse(t_vars *vars, int argc, char **argv);
int		is_whitespaces(char *line);
int		get_texture(char *line, t_map *map, int i);
int		get_color_id(char *line, t_map *map, int i);
int		get_map(char *line, t_map *map, int i);

// drawing_utils.c
int		cub_pixel_put(t_image *img, int x, int y, int color);
t_image *new_image(t_vars *vars, int width, int height, t_vector2 pos);
void	draw_square_tlc(t_image *img, int width, int height, int I_xtlc, int I_ytlc, int color);
void	draw_line(t_image *img, int I_xo, int I_yo, int I_xend, int I_yend, int color);
void	*loadimage(char *path, t_vars *vars, t_image *img_memory);

// inits
int		init_vars(t_vars *vars);
int		init_mlx_vars(t_vars *vars);
int		init_player(t_player *player);
// int		init_minimap(t_vars *vars);
int		init_minimap(t_minimap *minimap);

// hooks
int		mlx_hooks(t_vars *vars);
int		update(t_vars *vars);
int		on_key_down(int keycode, t_vars *vars);
int		on_key_up(int keycode, t_vars *vars);
int		exit_hook(t_vars *vars);

int	get_player_spawn(t_vars *vars);

// movement.c
void		set_dir(double angle, t_vector2 *dir);
double		correct_angle(double angle);
void		player_set_speed_angle(t_player *player, int *speed_forward, double *angle_offs);
t_vector2	player_get_newpos(t_player *player, int speed_forward, double new_angle);
int			player_next_x_obj(t_vars *vars);
int			player_next_y_obj(t_vars *vars);
int			player_prev_y_obj(t_vars *vars);
int			player_prev_x_obj(t_vars *vars);
int			player_check_x_pos(t_vars *vars, t_vector2 newpos);
int			player_check_y_pos(t_vars *vars, t_vector2 newpos);
void		player_move(t_vars *vars, t_player *player);



//system utils
double	get_fps(t_vars *vars);


// Alice
void	free_and_exit(t_vars *vars);
int		open_cubfile(t_map *map, char *path);

int		cub_dealkey(int keycode, t_vars *vars);


void	draw_minimap(t_vars *vars);
void	draw_player_minimap(t_vars *vars);

void	draw_all(t_vars *vars);


// merged
void		draw_tex_line(t_vars *vars, t_ray *ray, int line_height, t_image *src_img, int i);
t_vector2	new_vector2(double x, double y);
t_image 	*new_image_tex(t_vars *vars, char *tex_path);
int			on_mouse_move(int x, int y, t_vars *vars);

# endif
