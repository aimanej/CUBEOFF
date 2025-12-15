#include "../../includes/cub3d.h"

void render_func(t_mlx *mlx)
{
    static int check;
    if (check)
        ft_free_select(mlx->map.img.img_ptr);
        // mlx_destroy_image(mlx->mlx, mlx->map.img.img_ptr);
    mlx->map.img.img_ptr = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    ft_add_last_ptr(dump_ptr(), ft_new_ptr(mlx->map.img.img_ptr, 1));
    mlx->map.img.addr = mlx_get_data_addr(mlx->map.img.img_ptr, &(mlx->map.img.bpp), &(mlx->map.img.line_len), &(mlx->map.img.endian));
    ray_cast(&(mlx->map));
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->map.img.img_ptr, 0, 0);
    check = 1;
}

int wall_check(t_map *map, double row, double col)
{
    int coll = (int)(col / TILE_SIZE);
    int roww = (int)(row / TILE_SIZE);

    if (roww <= 0 || roww >= map->size - 1 || coll <= 0 || coll >= ft_strlen(map->map[roww]) - 1 || map->map[roww][coll] == '1')
        return 1;
    return 0;
}
