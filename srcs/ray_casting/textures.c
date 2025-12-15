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
        // printf("collumn in texture : %f\n", ray->texture_col);
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
    int pixel = 0;
    if(addr)
        pixel = *(int *)addr;

    int colors[3] = {(pixel >> 16) & 0xFF, (pixel >> 8) & 0xFF, pixel & 0xFF};
    double shade = 1 - (ray->wall_distance / 800);
    if (shade < 0.2)
    shade = 0.2;

    colors[0] *= shade;
    colors[1] *= shade;
    colors[2] *= shade;

    // {
    //     colors[t] /= grad;
    // }
    pixel = chimicolor(colors[0], colors[1], colors[2]);
    return pixel;
}
