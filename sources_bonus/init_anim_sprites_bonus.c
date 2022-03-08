#include "../header_bonus/cub3d_bonus.h"
#include <sys/time.h>

t_anim_sprite	*init_anim_sprite(t_vars *vars, char *path, int frame_count)
{
	int				i;
	t_anim_sprite	*anim_sprite;
	t_image 		**image;
	char			*full_path;
	struct			timeval curr_time;

	i = 1;
	anim_sprite	= malloc(sizeof(t_anim_sprite));
	image = malloc(sizeof(t_image *) * (frame_count) + 5000);
	if (!anim_sprite || !image)
	{
		printf("Failed to allocate memory for animated sprite.\n");
		free_and_exit(vars);
	}
	gettimeofday(&curr_time, NULL);
	anim_sprite->last_time_ms = curr_time.tv_usec + curr_time.tv_sec * 1000 * 1000;
	anim_sprite->anim_count = 1;
	anim_sprite->frame_count = frame_count;
	while (i <= frame_count)
	{
		full_path = ft_strjoin(path, ft_itoa(i));
		image[i] = new_image_tex(vars, full_path);
		free(full_path);
		i++;
	}
	anim_sprite->frames = image;
	return (anim_sprite);
}

void	anim_sprite(t_anim_sprite *anim_sprite, int frame_speed_ms)
{
	struct	timeval	curr_time;
	double	curr_time_ms;

	gettimeofday(&curr_time, NULL);
	curr_time_ms = curr_time.tv_usec + curr_time.tv_sec * 1000 * 1000;
	if (curr_time_ms - anim_sprite->last_time_ms >= frame_speed_ms)
	{
		anim_sprite->anim_count += 1;
		if (anim_sprite->anim_count > anim_sprite->frame_count)
			anim_sprite->anim_count = 1;
		anim_sprite->last_time_ms = curr_time_ms;
	}
}

