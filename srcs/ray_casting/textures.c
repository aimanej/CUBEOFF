#include "../../includes/cub3d.h"

void textures(t_map *map)
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

        ray->texture_col = (ray->texture_col * map->tex_width) / TILE_SIZE;
        t++;
    }
}

int getpixelcolor(t_map *map, int row, int col)
{
    if (row < 0)
        row = 0;
    if (row > map->tex_height)
        row = map->tex_height - 1;
    if (col < 0)
        col = 0;
    if (col > map->tex_width)
        col = map->tex_width - 1;

    char *addr = map->texture.addr + (map->texture.line_len * row) + (col * (map->texture.bpp / 8));
    int pixel = *(int *)addr;

    return pixel;
}
