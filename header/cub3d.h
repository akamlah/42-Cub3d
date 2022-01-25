#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"


// screen parameters
// window size (WW width, WH heigth in pixel)
# define WW 2560
# define WH 1600

typedef struct s_point
{
	int		x;
	int		y;
	int		wall;
	char	spawn_or;
}			t_point;

typedef struct s_map
{
	int		fd;
	t_point	**nodes;

}			t_map;

typedef struct s_vars
{
	//andi



	//alice
	t_map	*map;
}	t_vars;

// FUNCTIONS
//Andi




// Alice
int	parse(t_vars *vars, int argc, char **argv);



# endif