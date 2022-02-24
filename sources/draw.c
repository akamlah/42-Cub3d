#include "../header/cub3d.h"

void	raycast(t_vars *vars);

void draw_all(t_vars *vars)
{
	// tests
	// t_image *game;
	// game = new_image(vars, WW - 40, WH - 40, 20, 20);
	// // draw_square_tlc(game, game->width, game->height, 20, 20, 0xffffff); // boundary check for draw square ft.
	// draw_square_tlc(game, game->width, game->height, 0, 0, 0x808080);
	// int i, j;
	// i = 0;
	// while (vars->map->nodes[i] && i < vars->map->n_lines)
	// {
	// 	j = 0;
	// 	while (vars->map->nodes[i][j] && vars->map->nodes[i][j] != '\n')
	// 	{
	// 		if (j * RW_UNIT < game->width && i * RW_UNIT < game->height)
	// 			cub_pixel_put(game, j * RW_UNIT, i * RW_UNIT, 0xff0000);
	// 		j++;
	// 	}
	// 	i++;
	// }
	// cub_pixel_put(game, vars->player->RW_x, vars->player->RW_y, 0x00ff00);
	// mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, game->img_ptr, game->S_xtlc, game->S_ytlc);
	raycast(vars);
	draw_minimap(vars);
}


/////////////// UTILS ////////////////////

/*
	Draws a pixel in the given image given its image coordinate (x, y)
	and its color 'col'
*/
int	cub_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}

/*
	This function allocates memory for a new image and initialises it with the given size
	and position of its top left corner in the window (S_xtlc, S_ytlc) (values in pixel), and
	returns a pointer to it.
*/
t_image *new_image(t_vars *vars, int width, int height, int S_xtlc, int S_ytlc)
{
	t_image	*new_image;

	new_image = malloc(sizeof(t_image));
	new_image->width = width;
	new_image->height = height;
	new_image->S_xtlc = S_xtlc;
	new_image->S_ytlc = S_ytlc;
	new_image->img_ptr = mlx_new_image(vars->mlx_vars->mlx_ptr, new_image->width, new_image->height);
	new_image->address = mlx_get_data_addr(new_image->img_ptr, &new_image->bits_per_pixel, &new_image->line_length, &new_image->endian);
	return (new_image);
}

/*
	Draws a square sized 'xsize' * 'ysize' pixels given:
	- width and height in pixels
	- its top left corner (I_xtlc, I_ytlc) in IMAGE coordinates, in pixels
	- its color 'col'
	The if statement before drawing allows only pixels that actually fall into img boundaries to be drawn.
*/
void	draw_square_tlc(t_image *img, int width, int height, int I_xtlc, int I_ytlc, int color)
{
	int i;
	int j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if ((I_xtlc + j < img->width && I_ytlc + i < img->height)
				&& (I_xtlc >= 0 && I_ytlc >= 0))
				cub_pixel_put(img, I_xtlc + j, I_ytlc + i, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_image *img, int I_xo, int I_yo, int I_xend, int I_yend)
{
	int sx, sy, err, dx, dy, e2;
	dx = abs(I_xend - I_xo);
	if (I_xo < I_xend)
		sx = 1;
	else
		sx = -1;
	dy = -abs(I_yend - I_yo);
	if (I_yo < I_yend)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	while (1)
	{
<<<<<<< Updated upstream
		cub_pixel_put(img, xtl, ytl + i, col);
		cub_pixel_put(img, xtl + w, ytl + i, col);
		i++;
	}
	j = 0;
	while (j < w)
	{
		cub_pixel_put(img, xtl + j, ytl, col);
		cub_pixel_put(img, xtl + j, ytl + h, col);
		j++;
	}
}

void draw_player_minimap(t_vars *vars)
{
	int x, y, i;
	// int startx;
	// int starty;
	// int endx;
	// int endy;

	//y = atan(orientation)x + q;
	// startx = vars->player->px; // - vars->player->size / 2;

	x = 0;
	i = 0;
	while (i < 20 )
	{
		y = tan(0.4) * (x + vars->player->px) - vars->player->py;
		printf("%d %d\n", x, y);
		cub_pixel_put(vars->mlx_vars->minimap, x, y, 0xff0073);
		i++;
		x++;
	}
}


void	fill_minimap(t_vars *vars)
{
	int i;
	int j;
	int col;
	// minimap background?
	i = 0;
	while (vars->map->nodes[i] && i < vars->map->n_lines)
	{
		j = 0;
		while (vars->map->nodes[i][j] && vars->map->nodes[i][j] != '\n')
		{
			if (vars->map->nodes[i][j] == 'N' || vars->map->nodes[i][j] == 'S' || vars->map->nodes[i][j] == 'W' || vars->map->nodes[i][j] == 'E')
			{
				if (vars->map->nodes[i][j] == 'N')
					vars->player->orientation = 0;
				if (vars->map->nodes[i][j] == 'W')
					vars->player->orientation = M_PI;
				if (vars->map->nodes[i][j] == 'S')
					vars->player->orientation = 2 * M_PI / 3;
				if (vars->map->nodes[i][j] == 'E')
					vars->player->orientation = 0;
				vars->player->px = j * vars->minimap_scale + vars->minimap_scale / 2 - vars->player->size / 2;
				vars->player->py = i * vars->minimap_scale + vars->minimap_scale / 2 - vars->player->size / 2;
				vars->map->nodes[i][j] = '0';
			}
			if (vars->map->nodes[i][j] == '1')
				col = 1;
			else
				col = 0;
			if (vars->map->nodes[i][j] == '1' || vars->map->nodes[i][j] == '0')
			{
				draw_square_tlc(vars->mlx_vars->minimap, vars->minimap_scale - 1, vars->minimap_scale - 1, \
				(j * vars->minimap_scale + vars->minimap_xframeoffset), \
				(i * vars->minimap_scale + vars->minimap_yframeoffset), col * 0xffffff);
			}
			j++;
=======
		cub_pixel_put(img, I_xo, I_yo, 0x00ff00);
		if (I_xo == I_xend && I_yo == I_yend)
			break ;
		e2 = 2 * err;
		if (e2 > dy)
		{
			err += dy;
			I_xo += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			I_yo += sy;
>>>>>>> Stashed changes
		}
	}
<<<<<<< Updated upstream
}

void	draw_minimap(t_vars *vars)
{
	vars->minimap_xframeoffset = 10;
	vars->minimap_yframeoffset = 10;
	vars->minimap_xframelen = vars->minimap_scale * (vars->map->max_width - 1) + vars->minimap_xframeoffset * 2;
	vars->minimap_yframelen = vars->minimap_scale * vars->map->n_lines + vars->minimap_yframeoffset * 2;
	vars->mlx_vars->minimap = malloc(sizeof(t_image));
	vars->mlx_vars->minimap->ref = mlx_new_image(vars->mlx_vars->mlx_ref, vars->minimap_xframelen, \
		vars->minimap_yframelen);
	vars->mlx_vars->minimap->address = mlx_get_data_addr(vars->mlx_vars->minimap->ref, \
		&vars->mlx_vars->minimap->bits_per_pixel, &vars->mlx_vars->minimap->line_length, \
		&vars->mlx_vars->minimap->endian);
	draw_square_tlc(vars->mlx_vars->minimap, vars->minimap_xframelen - 4, vars->minimap_yframelen - 4, 2, 2, 0x809672);
	draw_frame(vars->mlx_vars->minimap, vars->minimap_xframelen - 1, vars->minimap_yframelen -1, 0, 0, 0xf4f2f3);
	fill_minimap(vars);
	draw_player_minimap(vars);
	vars->minimap_xwinoffset = 20;
	vars->minimap_ywinoffset = WH - vars->minimap_yframelen - 20;
	mlx_put_image_to_window(vars->mlx_vars->mlx_ref, vars->mlx_vars->window, vars->mlx_vars->minimap->ref, \
	vars->minimap_xwinoffset, vars->minimap_ywinoffset);
}

void	draw_background(t_vars *vars)
{
	vars->mlx_vars->background = malloc(sizeof(t_image));
	vars->mlx_vars->background->ref = mlx_new_image(vars->mlx_vars->mlx_ref, WW, WH);
	vars->mlx_vars->background->address = mlx_get_data_addr(vars->mlx_vars->background->ref, &vars->mlx_vars->background->bits_per_pixel, &vars->mlx_vars->background->line_length, &vars->mlx_vars->background->endian);

	draw_square_tlc(vars->mlx_vars->background, WW, WH, 0, 0, 0x1e1a1c);
	draw_frame(vars->mlx_vars->background, WW - 10, WH - 10, 5, 5, 0xf4f2f3);

	mlx_put_image_to_window(vars->mlx_vars->mlx_ref, vars->mlx_vars->window, vars->mlx_vars->background->ref, 0, 0);
}


void render_raycast(t_vars *vars)
{
	vars->mlx_vars->raycast = malloc(sizeof(t_image));
	vars->mlx_vars->raycast->ref = mlx_new_image(vars->mlx_vars->mlx_ref, WW - 100, WH - 100);
	vars->mlx_vars->raycast->address = mlx_get_data_addr(vars->mlx_vars->raycast->ref, \
	&vars->mlx_vars->raycast->bits_per_pixel, &vars->mlx_vars->raycast->line_length, \
	&vars->mlx_vars->raycast->endian);

	draw_square_tlc(vars->mlx_vars->raycast, WW - 100, WH - 100, 0, 0, 0xffffff);
	

	mlx_put_image_to_window(vars->mlx_vars->mlx_ref, vars->mlx_vars->window, \
	vars->mlx_vars->raycast->ref, 50, 50);
}

void compone_window(t_vars *vars)
{

	draw_background(vars);
	render_raycast(vars);
	draw_minimap(vars);

	// write player coord on screen:
	char *tmp;
	tmp = ft_strjoin("Player x coordinate: ", ft_itoa(vars->player->px));
	mlx_string_put(vars->mlx_vars->mlx_ref, vars->mlx_vars->window, 10, 10, 0xffffff, tmp);
	free(tmp);
	tmp = ft_strjoin("Player y coordinate: ", ft_itoa(vars->player->py));
	mlx_string_put(vars->mlx_vars->mlx_ref, vars->mlx_vars->window, 10, 30, 0xffffff, tmp);
	free(tmp);
}
=======
}
>>>>>>> Stashed changes
