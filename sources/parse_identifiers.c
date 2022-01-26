#include "../header/cub3d.h"

int	is_whitespaces(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	handle_tex_id(int i, char *id, char **map_ptr, char *line)
{
	if (*map_ptr)
	{
		printf("Error\nLine %d: Duplicate identifier `%s'\n", i + 1, id);
		return (0);
	}
	*map_ptr = ft_strdup(line + 3);
	return (1);
}

int	get_texture(char *line, t_map *map, int i)
{
	if (!line[0] || !line[1] || !line[2])
		return (0);
	if (line [2] != ' ')
		return (0);
	if (line[0] == 'N' && line[1] == 'O')
		return (handle_tex_id(i, "NO", &(map->textr_n), line));
	if (line[0] == 'S' && line[1] == 'O')
		return (handle_tex_id(i, "SO", &(map->textr_s), line));
	if (line[0] == 'W' && line[1] == 'E')
		return (handle_tex_id(i, "WE", &(map->textr_w), line));
	if (line[0] == 'E' && line[1] == 'A')
		return (handle_tex_id(i, "EA", &(map->textr_e), line));
	return (0);
}

int	get_color_id(char *line, t_map *map)
{
	if (!line[0] || !line[1])
		return (0);
	if (line [1] != ' ')
		return (0);
	if (line[0] == 'F')
	{
		map->floor_color = ft_strdup(line + 2);
		return (1);
	}
	if (line[0] == 'C')
	{
		map->ceiling_color = ft_strdup(line + 2);
		return (1);
	}
	return (0);
}
