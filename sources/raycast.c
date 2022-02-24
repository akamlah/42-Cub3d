#include "../header/cub3d.h"

void	raycast(t_vars *vars)
{
	vars->prjp = new_image(vars, PRJP_W, PRJP_H, 20, 20);
	int dx, dy, sx, sy, intxx, intxy;
	if (vars->player->th < M_PI / 2 && vars->player->th > 0)
	{
		// horizontal distance to first vertical line
		dx = RW_UNIT - (vars->player->RW_x % RW_UNIT);
		// vertical distance to first horizontal line
		dy = vars->player->RW_y % RW_UNIT;
		if (dx > dy)
		{
			// vertical distance to first vertial intersection
			sy = dx * tan(vars->player->th);
			intxy = vars->player->RW_y - sy;
			// draw_line(vars->prjp, )
		}
	}
	sx = 0;
	intxx = 0;
	// put to window
	mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
		vars->mlx_vars->win_ptr, \
		vars->prjp->img_ptr, \
		vars->prjp->S_xtlc, \
		vars->prjp->S_ytlc);
}
