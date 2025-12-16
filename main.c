#include "includes/cub3d.h"

int	main(int ac, char **av)
{
	t_mlx	mlx;

	(void)ac;
	mlx.mlx = mlx_init();
	ft_add_last_ptr(dump_ptr(), ft_new_ptr(&mlx, 0));
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "WINDOW");
	map_init(&mlx);
	parsing(av, &(mlx.map));
	mlx.map.screenw = WIDTH;
	init_ray_arr(&(mlx.map));
	texture_init(&(mlx));
	render_func(&mlx);
	mlx_hook_loops(&mlx);
}
