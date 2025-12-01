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
            ray->texture_col = (ray->texture_col * map->tex_no.width) / TILE_SIZE;
        else if (ray->compass == SO)
            ray->texture_col = (ray->texture_col * map->tex_so.width) / TILE_SIZE;
        else if (ray->compass == EA)
            ray->texture_col = (ray->texture_col * map->tex_ea.width) / TILE_SIZE;
        else if (ray->compass == WE)
            ray->texture_col = (ray->texture_col * map->tex_we.width) / TILE_SIZE;
        t++;
    }
}

int getpixelcolor(t_map *map, t_ray *ray, int row, int col)
{

    if (ray->compass == NO)
    {
        if (row < 0)
            row = 0;
        if (row > map->tex_no.height)
            row = map->tex_no.height - 1;
        if (col < 0)
            col = 0;
        if (col > map->tex_no.width)
            col = map->tex_no.width - 1;
        char *addr = map->tex_no.addr + (map->tex_no.line_len * row) + (col * (map->tex_no.bpp / 8));
        int pixel = *(int *)addr;

        return pixel;
    }
    else if (ray->compass == SO)
    {
        if (row < 0)
            row = 0;
        if (row > map->tex_so.height)
            row = map->tex_so.height - 1;
        if (col < 0)
            col = 0;
        if (col > map->tex_so.width)
            col = map->tex_so.width - 1;
        char *addr = map->tex_so.addr + (map->tex_so.line_len * row) + (col * (map->tex_so.bpp / 8));
        int pixel = *(int *)addr;

        return pixel;
    }
    else if (ray->compass == EA)
    {
        if (row < 0)
            row = 0;
        if (row > map->tex_ea.height)
            row = map->tex_ea.height - 1;
        if (col < 0)
            col = 0;
        if (col > map->tex_ea.width)
            col = map->tex_ea.width - 1;
        char *addr = map->tex_ea.addr + (map->tex_ea.line_len * row) + (col * (map->tex_ea.bpp / 8));
        int pixel = *(int *)addr;

        return pixel;
    }
    else if (ray->compass == WE)
    {
        if (row < 0)
            row = 0;
        if (row > map->tex_we.height)
            row = map->tex_we.height - 1;
        if (col < 0)
            col = 0;
        if (col > map->tex_we.width)
            col = map->tex_we.width - 1;
        char *addr = map->tex_we.addr + (map->tex_we.line_len * row) + (col * (map->tex_we.bpp / 8));
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
