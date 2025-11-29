#include "../../includes/cub3d.h"

int gameloop(void *data)
{
    t_mlx *mlx = data;

    player_update(&(mlx->map));
    if (mlx->map.player.turn_dir || mlx->map.player.walk_dir)
    {
        mlx_destroy_image(mlx->mlx, mlx->map.img.img_ptr);
        mlx->map.img.img_ptr = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
        mlx->map.img.addr = mlx_get_data_addr(mlx->map.img.img_ptr, &(mlx->map.img.bpp), &(mlx->map.img.line_len), &(mlx->map.img.endian));
        render_func(mlx);
    }
}
