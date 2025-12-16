#include "../../includes/cub3d.h"

int	gameloop(void *data)
{
	t_mlx	*mlx;

	mlx = data;
	if (mlx->map.player.turn_dir || mlx->map.player.walk_dir
		|| mlx->map.player.side_walk)
	{
		player_update(&(mlx->map));
		render_func(mlx);
	}
}

void	render_func(t_mlx *mlx)
{
	if (mlx->map.img.img_ptr)
		ft_free_select(mlx->map.img.img_ptr);
	mlx->map.img.img_ptr = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	ft_add_last_ptr(dump_ptr(), ft_new_ptr(mlx->map.img.img_ptr, 1));
	mlx->map.img.addr = mlx_get_data_addr(mlx->map.img.img_ptr,
			&(mlx->map.img.bpp), &(mlx->map.img.line_len),
			&(mlx->map.img.endian));
	ray_cast(&(mlx->map));
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->map.img.img_ptr, 0, 0);
}
