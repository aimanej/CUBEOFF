#include "../includes/cub3d.h"


int chimicolor(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void draw_to_img(t_image *img, int row, int col, int color)
{
    char *ptr;

    ptr = img->addr + (img->line_len * row) + (col * (img->bpp / 8));
    *(int *)ptr = color;
}

void paint_wall(t_map *map, t_ray *ray, int cur_col)
{

    double tex_row = 0;
    double step = map->textures[ray->compass].height / ray->unclipped;

    if (ray->unclipped > HEIGHT)
    {
        double t = (1 - (HEIGHT / ray->unclipped)) / 2;
        tex_row = t * (double)(map->textures[ray->compass].height);
    }
    while (ray->row_start < ray->row_end)
    {
        if (cur_col > WIDTH - 1 || ray->row_start > HEIGHT - 1 || cur_col < 0 || ray->row_start < 0)
            break;
        int color = getpixelcolor(map, ray, tex_row, ray->texture_col);
        tex_row += step;
        draw_to_img(&(map->img), ray->row_start, cur_col, color);
        ray->row_start++;
    }
}

void paint_ceiling(t_map *map, t_ray *ray, int cur_col)
{
    int p = 0;
    while (p < ray->row_start)
    {
        if (cur_col > WIDTH - 1 || p > HEIGHT - 1 || cur_col < 0 || p < 0)
            break;
        draw_to_img(&(map->img), p, cur_col, map->ceil_color);
        p++;
    }
}

void paint_floor(t_map *map, t_ray *ray, int cur_col)
{
    while (ray->row_end < HEIGHT)
    {
        if (cur_col > WIDTH - 1 || ray->row_end > HEIGHT - 1 || cur_col < 0 || ray->row_end < 0)
            break;
        draw_to_img(&(map->img), ray->row_end, cur_col, map->fl_color);
        ray->row_end++;
    }
}

