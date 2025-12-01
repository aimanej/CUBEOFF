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
        if (ray->compass == NO)
            ray->texture_col = (ray->texture_col * map->tex1.width) / TILE_SIZE;
        else if (ray->compass == SO)
            ray->texture_col = (ray->texture_col * map->tex2.width) / TILE_SIZE;
        else if (ray->compass == EA)
            ray->texture_col = (ray->texture_col * map->tex3.width) / TILE_SIZE;
        else if (ray->compass == WE)
            ray->texture_col = (ray->texture_col * map->tex4.width) / TILE_SIZE;
        t++;
    }
}

int getpixelcolor(t_map *map, t_ray *ray, int row, int col)
{

    if (ray->compass == NO)
    {
        if (row < 0)
            row = 0;
        if (row > map->tex1.height)
            row = map->tex1.height - 1;
        if (col < 0)
            col = 0;
        if (col > map->tex1.width)
            col = map->tex1.width - 1;
        char *addr = map->tex1.addr + (map->tex1.line_len * row) + (col * (map->tex1.bpp / 8));
        int pixel = *(int *)addr;

        return pixel;
    }
    else if (ray->compass == SO)
    {
        if (row < 0)
            row = 0;
        if (row > map->tex2.height)
            row = map->tex2.height - 1;
        if (col < 0)
            col = 0;
        if (col > map->tex2.width)
            col = map->tex2.width - 1;
        char *addr = map->tex2.addr + (map->tex2.line_len * row) + (col * (map->tex2.bpp / 8));
        int pixel = *(int *)addr;

        return pixel;
    }
    else if (ray->compass == EA)
    {
        if (row < 0)
            row = 0;
        if (row > map->tex3.height)
            row = map->tex3.height - 1;
        if (col < 0)
            col = 0;
        if (col > map->tex3.width)
            col = map->tex3.width - 1;
        char *addr = map->tex3.addr + (map->tex3.line_len * row) + (col * (map->tex3.bpp / 8));
        int pixel = *(int *)addr;

        return pixel;
    }
    else if (ray->compass == WE)
    {
        if (row < 0)
            row = 0;
        if (row > map->tex4.height)
            row = map->tex4.height - 1;
        if (col < 0)
            col = 0;
        if (col > map->tex4.width)
            col = map->tex4.width - 1;
        char *addr = map->tex4.addr + (map->tex4.line_len * row) + (col * (map->tex4.bpp / 8));
        int pixel = *(int *)addr;

        return pixel;
    }
    // if (row < 0)
    //     row = 0;
    // if (row > map->tex_height)
    //     row = map->tex_height - 1;
    // if (col < 0)
    //     col = 0;
    // if (col > map->tex_width)
    //     col = map->tex_width - 1;

    // char *addr = map->texture.addr + (map->texture.line_len * row) + (col * (map->texture.bpp / 8));
    // int pixel = *(int *)addr;

    return 0;
}
