#include "../header/cub3d.h"


/*
	The map must be composed of only 6 possible characters: 0 for an empty space,
	1 for a wall, and N,S,E or W for the player’s start position and spawning
	orientation.

	The map must be closed/surrounded by walls, if not the program must return
	an error.

	Except for the map content, each type of element can be separated by one or
	more empty line(s).

	Except for the map content which always has to be the last, each type of
	element can be set in any order in the file.

	Except for the map, each type of information from an element can be separated
	by one or more space(s).

	Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each
	object in a strict order such as :
	∗ North texture:
	NO ./path_to_the_north_texture
	· identifier: NO
	· path to the north texure
	∗ South texture:
	SO ./path_to_the_south_texture
	· identifier: SO
	· path to the south texure
	∗ West texture:
	WE ./path_to_the_west_texture
	· identifier: WE
	· path to the west texure
	∗ East texture:
	EA ./path_to_the_east_texture
	· identifier: EA
	· path to the east texure
	∗ Floor color:
	F 220,100,0
	· identifier: F
	· R,G,B colors in range [0,255]: 0, 255, 255
	∗ Ceilling color:
	C 225,30,0
	· identifier: C
	· R,G,B colors in range [0,255]: 0, 255, 255
	If any misconfiguration of any kind is encountered in the file, the program
	must exit properly and return "Error\n" followed by an explicit error message
	of your choice.
*/
void	print_usage_message()
{
	printf("Usage: ./cub3D <path to map>\n");
}

int	parse(t_vars *vars, int argc, char **argv)
{
	t_map	map;
	char	*buff;
	int i;

	vars->map = &map;
	if (argc != 2)
	{
		print_usage_message();
		return (0);
	}
	map.fd = open(argv[1], O_RDONLY);
	i = 0;
	buff = "1";
	while (buff)
	{
		buff = get_next_line(map.fd);
		printf("%s\n", buff);
		i++;
	}
	return (0);
}
