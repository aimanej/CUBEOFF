#include "../../includes/cub3d.h"


void render_func(t_mlx *mlx)
{
    ray_cast(&(mlx->map));
    minimap(mlx);
    draw_player(&(mlx->map));
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->map.img.img_ptr, 0, 0);
}

int wall_check(t_map *map, double row, double col)
{
    int coll = floor((int)(col / TILE_SIZE));
    int roww = floor((int)(row / TILE_SIZE));
    // printf("coll : %d roww %d position checked : %c\n", coll, roww, map->map[roww][coll]);

    if (coll <= 0 || coll >= map->len - 1 || roww <= 0 || roww >= map->size - 1 || map->map[roww][coll] == '1')
        return 1;
    return 0;
}
