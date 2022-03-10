/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mandatory.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:05:28 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/10 15:57:48 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MANDATORY_H
# define CUB3D_MANDATORY_H

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <limits.h>

# define MAIN_IMG_W 1280
# define MAIN_IMG_H 1024

// distance from window border of game window.
# define MAIN_IMG_WIN_OFFSET 20

# define SIDEBAR_W	250

// the size of one element of the map
# define SCALE 64

// field of view (angle, in rad)
# define FOV_DEG 60
# define FOV_RAD 1.0471975512

// one degree in radians
# define ONE_DEG_RAD 0.0174533

//Maximum map-square number value for parsing
# define MAX_OBJ_CHAR '2'

//keycodes
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_A 0
# define KEY_D 2
# define KEY_W 13
# define KEY_S 1
# define KEY_ESC 53
# define KEY_SPACE 49
# define KEY_LSHIFT 258
# define KEY_RSHIFT 257

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

typedef struct s_image
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

typedef struct s_ray
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
	double		hor_hit_player_dist;
	double		vert_hit_player_dist;
	int			wall_height;
	char		hit_char;
}				t_ray;

typedef struct mlx_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
}			t_mlx_vars;

typedef struct s_player
{
	t_vector2	pos;
	t_vector2	spawn_pos;
	double		spawn_angle;
	double		angle;
	double		rot_speed;
	double		rot_slow_speed;
	double		rot_fast_speed;
	double		speed;
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
	int			size;
}				t_player;

typedef struct s_vars
{
	int				move_forward;
	t_mlx_vars		*mlx_vars;
	t_map			*map;
	t_player		player;
	t_image			*main_img;
	t_image			*tex_n;
	t_image			*tex_s;
	t_image			*tex_e;
	t_image			*tex_w;
	double			last_time_ms;
	double			prj_pane_dist;
	int				floor_color;
	int				ceiling_color;
	int				winw;
	int				winh;
	double			ray_ang_incr;
}	t_vars;

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
int			parse_colors(t_vars *vars);

//			main.c
void		exit_cub(void);

//	PARSER ---------------------------------------------------------------------
//			parse_identifiers.c (+2 statics):
int			is_whitespaces(char *line);
int			get_texture(char *line, t_map *map, int i);
int			get_color_id(char *line, t_map *map, int i);
//			parse_map.c (+1 statics):
int			parse_map_lines(t_vars *vars);
//			parse.c (+2 statics):
int			parse(t_vars *vars, char **argv);
void		print_usage_message(int msg);
int			open_cubfile(t_map *map, char *path);
//			parse_map_chars.c (+2 statics):
int			get_map(char *line, t_map *map, int i);
int			is_valid_c(char c);
//			parse_map_check_borders.c (+3 statics):
int			check_borders(t_vars *vars, char **maplines);
//			parse_map_check_map.c (+4 statics):
int			check_map(t_vars *vars, char	**maplines);
//			parse_map_checkers.c:
int			check_top(char **maplines, t_vector2_int pos, char checkchar);
int			check_bot(t_vars *vars, char **maplines, t_vector2_int pos, \
			char checkchar);
int			check_lr(char **maplines, t_vector2_int pos, char checkchar);
int			check_top_space(char **maplines, t_vector2_int pos);
int			check_bot_space(t_vars *vars, char **maplines, t_vector2_int pos);

//------------------------------------------------------------------------------

//	inits.c
int			init_vars(t_vars *vars);
int			init_mlx_vars(t_vars *vars);
int			init_player(t_player *player);

// player_spawn.c (+1 static)
int			get_player_spawn(t_vars *vars);

// draw.c
void		render(t_vars *vars);
int			update(t_vars *vars);

// sidebar
void		draw_sidebar_start(t_vars *vars);
void		display_data_sidebar(t_vars *vars);

//------------------------------------------------------------------------------
//	RAYCASTER
void		raycast(t_vars *vars);
//			cast a ray
void		cast_ray(t_vars *vars, t_ray *ray);
//			utils
int			is_point_in_map(t_vars *vars, t_vector2	point);
int			point_iswall(t_vars *vars, double RW_x, double RW_y, t_ray *ray);
void		ray_set_vars_to_start(t_ray *ray);
void		draw_sun(t_vars *vars, t_ray *ray, int i);
void		draw_wall(t_vars *vars, t_ray *ray, int i);

//	drawing_utils.c
int			cub_pixel_put(t_image *img, int x, int y, int color);
t_image		*new_image(t_vars *vars, int width, int height, t_vector2 pos);
void		draw_square_tlc(t_image *img, t_vector2_int size, \
			t_vector2_int pos, int color);
void		*loadimage(char *path, t_vars *vars, t_image *img_memory);
t_image		*new_image_tex(t_vars *vars, char *tex_path);

// vector_utils.c
t_vector2	new_vector2(double x, double y);

// texture_map.c
void		draw_tex_line(t_vars *vars, t_ray *ray, t_image *src_img, int i);

//------------------------------------------------------------------------------
// INTERACTIONS
//	mlx.c
int			mlx_hooks(t_vars *vars);
int			on_key_down(int keycode, t_vars *vars);
int			on_key_up(int keycode, t_vars *vars);
int			exit_hook(void);

//	movement.c (+4 statics)
void		player_move(t_vars *vars, t_player *player);
// movement_newpos.c
t_vector2	player_get_newpos(t_player *player, int speed_forward, \
			double new_angle);
int			player_next_x_obj(t_vars *vars);
int			player_next_y_obj(t_vars *vars);
int			player_prev_y_obj(t_vars *vars);
int			player_prev_x_obj(t_vars *vars);
// movement_checkpos.c
int			player_check_x_pos(t_vars *vars, t_vector2 newpos);
int			player_check_y_pos(t_vars *vars, t_vector2 newpos);

#endif
