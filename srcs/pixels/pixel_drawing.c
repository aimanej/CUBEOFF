#include "../../includes/cub3d.h"

void render_func(t_mlx *mlx)
{
    static int check;
    if (check)
        mlx_destroy_image(mlx->mlx, mlx->map.img.img_ptr);
    mlx->map.img.img_ptr = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    mlx->map.img.addr = mlx_get_data_addr(mlx->map.img.img_ptr, &(mlx->map.img.bpp), &(mlx->map.img.line_len), &(mlx->map.img.endian));
    ray_cast(&(mlx->map));
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->map.img.img_ptr, 0, 0);
    check = 1;
}

// void mini_rays(t_map *map)
// {
//     int t = 0;

//     while (t < map->screenw)
//     {
//         t_ray *ray = map->ray_arr[t];
//         double distance = ray->wall_distance;
//         double row = map->player.center_pos.row;
//         double col = map->player.center_pos.col;
//         while (AB_distance(map->player.center_pos.row, map->player.center_pos.col, row, col) <= distance)
//         {

//             draw_to_img(&(map->img), row * SCALE, col * SCALE, chimicolor(0, 0, 155));
//             row += sin(ray->angle);
//             col += cos(ray->angle);
//         }
//         // printf("distance to wall : %f -- distance end loop %f\n", distance, AB_distance(map->player.center_pos.row, map->player.center_pos.col, row, col));
//         t++;
//     }
// }

int wall_check(t_map *map, double row, double col)
{
    int coll = floor((int)(col / TILE_SIZE));
    int roww = floor((int)(row / TILE_SIZE));
    // printf("coll : %d roww %d position checked : %c\n", coll, roww, map->map[roww][coll]);

    if (coll <= 0 || coll >= map->len - 1 || roww <= 0 || roww >= map->size - 1 || map->map[roww][coll] == '1')
        return 1;
    return 0;
}
