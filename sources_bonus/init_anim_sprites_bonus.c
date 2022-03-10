/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anim_sprites_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:03:28 by agebert           #+#    #+#             */
/*   Updated: 2022/03/10 16:07:10 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"
#include <sys/time.h>

struct s_variables{
	int				i;
	t_image			**image;
	char			*full_path;
	char			*frame_num;
	struct timeval	curr_time;
};

t_anim_sprite	*init_localvars(t_vars *vars, \
					struct s_variables *local_vars, \
					int frame_count)
{
	t_anim_sprite	*anim_sprite;
	void			*ftheflags;

	ftheflags = vars;
	local_vars->i = 1;
	anim_sprite = malloc(sizeof(t_anim_sprite));
	local_vars->image = malloc(sizeof(t_image) * (frame_count));
	if (!anim_sprite || !local_vars->image)
	{
		printf("Failed to allocate memory for animated sprite.\n");
		exit_cub();
	}
	gettimeofday(&local_vars->curr_time, NULL);
	anim_sprite->last_time_ms = \
		local_vars->curr_time.tv_usec \
		+ local_vars->curr_time.tv_sec * 1000 * 1000;
	anim_sprite->anim_count = 1;
	anim_sprite->frame_count = frame_count;
	return (anim_sprite);
}

t_anim_sprite	*init_anim_sprite(t_vars *vars, char *path, int frame_count)
{
	t_anim_sprite		*anim_sprite;
	struct s_variables	local_vars;

	anim_sprite = init_localvars(vars, &local_vars, frame_count);
	while (local_vars.i <= frame_count)
	{
		local_vars.frame_num = ft_itoa(local_vars.i);
		local_vars.full_path = ft_strjoin(path, local_vars.frame_num);
		local_vars.image[local_vars.i] = \
			new_image_tex(vars, local_vars.full_path);
		free(local_vars.full_path);
		free(local_vars.frame_num);
		local_vars.i++;
	}
	anim_sprite->frames = local_vars.image;
	return (anim_sprite);
}

void	anim_sprite(t_anim_sprite *anim_sprite, int frame_speed_ms)
{
	struct timeval	curr_time;
	double			curr_time_ms;

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
