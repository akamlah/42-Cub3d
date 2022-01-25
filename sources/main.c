#include "../header/cub3D.h"

int main(int argc, char **argv)
{
	t_vars vars;

	if (parse(&vars, argc, argv))
		return (1);
	printf("yo\n");
	return (0);
}
