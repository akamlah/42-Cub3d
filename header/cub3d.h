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

# define MAIN_IMG_W 1280
# define MAIN_IMG_H 1024


// distance from window border of game window.
#define MAIN_IMG_WIN_OFFSET 20

# define SIDEBAR_W	250
# define WW (MAIN_IMG_W + SIDEBAR_W + MAIN_IMG_WIN_OFFSET * 2)
# define WH (MAIN_IMG_H + MAIN_IMG_WIN_OFFSET * 2)

// the size of one element of the map, ie. a wall or floor tile, in real world coordinates.
# define SCALE 64

// parameters for the positionig of the full map on screen
# define FUL_MAP_MAIN_IMG_OFFSET 100
# define FULL_MAP_WIN_OFFSET (MAIN_IMG_WIN_OFFSET + FUL_MAP_MAIN_IMG_OFFSET)

// field of view (angle, in rad)
# define FOV_DEG 60
# define FOV_RAD (M_PI / 3)

# define PLAYER_SIZE_RW (SCALE / 10)

// angular distance between rays when casting within the field of view
# define RAY_ANG_INCREMENT (FOV_RAD / MAIN_IMG_W)

// one degree in radians
# define ONE_DEG_RAD 0.0174533

//Maximum map-square number value for parsing
# define MAX_OBJ_CHAR '2'

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
# define key_tab 48
# define key_space 49
# define key_Lshift 258
# define key_Rshift 257

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
	char	**nodes;
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
	void			*img_ptr;
	char			*address;
	t_vector2		pos;
}				t_image;

typedef	struct	s_anim_sprite
{
	t_image **frames;
	double	last_time_ms;
	int		frame_count;
	int		anim_count;
}				t_anim_sprite;

typedef struct	s_ray
{
	t_vector2	hor_hit;
	t_vector2	vert_hit;
	t_vector2	closest_hit;
	int			x_increment_dir;
	int			y_increment_dir;
	double		distance;
	double		angle;
	double		hor_dx;
	double		hor_dy;
	double		vert_dx;
	double		vert_dy;
	int			facing_direction;
	double		hor_hit_player_dist_RW;
	double		vert_hit_player_dist_RW;
	int			wall_height;
	char		hit_char;
	double		darkening_factor;
}				t_ray;

typedef struct mlx_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		*minimap;
}			t_mlx_vars;

typedef struct s_player
{
	t_vector2	pos; //actual player position in game world (grid)
	t_vector2	spawn_pos;
	double		spawn_angle;
	double		angle; //player angle

	double		rot_speed;
	double		rot_slow_speed;
	double		rot_fast_speed;
	double		speed; //player movement speed;
	double		basic_speed;
	double		sprinting_speed;
	char		move_forward;
	char		move_backward;
	char		move_left;
	char		move_right;
	char		rotate_left;
	char		rotate_right;
	int			mouse_last_x;
	t_vector2	dir;
}				t_player;

typedef struct s_minimap
{
	// t_image	*img; // need to alloc
	int		scale;
	t_vector2	p_pos;
	int		width;
	int		height;
	int		total_width;
	int		total_height;

	int		player_size;

	int		wall_color;
	int		floor_color;
	int		background_color;
	int		player_color;
	int		ray_color;

	int		h_offs;
	int		w_offs;
}				t_minimap;

typedef struct s_full_map
{
	int			max_width;
	int			max_height;
	int			width;
	int			height;
	int			blocksize;
	t_vector2	top_left_corner_pos;
	t_image		*img;
	int			player_size;
}				t_full_map;

typedef struct s_vars
{
	int			move_forward;
	t_mlx_vars		*mlx_vars;
	t_map			*map;
	t_player		player;
	t_minimap		minimap;
	t_full_map		full_map;
	t_image			*main_img;
	t_image			*tex_N;
	t_image			*tex_S;
	t_image			*tex_E;
	t_image			*tex_W;
	t_anim_sprite	*mario_dance;
	t_image			*tex_door;
	int			display_full_map;

	double		last_time_ms;
	double		prj_pane_dist;

}	t_vars;


// FUNCTIONS

void	free_and_exit(t_vars *vars);
// parser
int		open_cubfile(t_map *map, char *path);
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

int		get_player_spawn(t_vars *vars);

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


// draw function in render loop
void	render(t_vars *vars);

void	draw_blocks_map(t_vars *vars, t_image *map_img, int	blocksize);

// minimap
int		create_minimap(t_vars *vars);
void	draw_minimap(t_vars *vars);
void	draw_player_minimap(t_vars *vars);
void	draw_ray_minimap(t_vars *vars, t_ray *ray);


// fullmap
int		create_fullmap(t_vars *vars);
void	draw_ray_fullmap(t_vars *vars, t_ray *ray);
void	draw_full_map(t_vars *vars);
void	draw_player_full_map(t_vars *vars);
void	draw_blocks_full_map(t_vars *vars, t_image *map_img, int blocksize);

// sidebar
void	draw_sidebar_start(t_vars *vars);
void	display_data_sidebar(t_vars *vars);



// merged
void			draw_tex_line(t_vars *vars, t_ray *ray, int line_height, t_image *src_img, int i);
t_vector2		new_vector2(double x, double y);
t_image 		*new_image_tex(t_vars *vars, char *tex_path);
int				on_mouse_move(int x, int y, t_vars *vars);
t_anim_sprite	*init_anim_sprite(t_vars *vars, char *path, int frame_count);
void			anim_sprite(t_anim_sprite *anim_sprite, int frame_speed_ms);
# endif
