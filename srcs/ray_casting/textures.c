#include "../../includes/cub3d.h"

void texture_col_int(t_map *map)
{
    int t = 0;

    while (t < WIDTH)
    {
        t_ray *ray = map->ray_arr[t];
        if (ray->hor_wall_distance < ray->ver_wall_distance)
        {
            ray->texture_col = ray->wallhit_col;
        }
        else
            ray->texture_col = ray->wallhit_row;
        ray->texture_col = fmod(ray->texture_col, TILE_SIZE);
        ray->texture_col = (ray->texture_col * map->textures[ray->compass].width) / TILE_SIZE;
        t++;
    }
}

int getpixelcolor(t_map *map, t_ray *ray, int row, int col)
{

    if (row < 0)
        row = 0;
    if (row > map->textures[ray->compass].height)
        row = map->textures[ray->compass].height - 1;
    if (col < 0)
        col = 0;
    if (col > map->textures[ray->compass].width)
        col = map->textures[ray->compass].width - 1;
    char *addr = map->textures[ray->compass].addr + (map->textures[ray->compass].line_len * row) + (col * (map->textures[ray->compass].bpp / 8));
    int pixel = *(int *)addr;

    return pixel;
}
