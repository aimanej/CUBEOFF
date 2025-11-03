#include "cub3d.h"

int chimicolor(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

// int keyhook(int keysym, void *data)
// {
//     t_cube *cube = data;
//     mlx_destroy_window(cube->mlx, cube->window);
// }

void draw_to_img(t_image *img, int x, int y, int color)
{
    char *ptr;

    ptr = img->addr + (img->line_len * y) + (x * (img->bpp / 8));
    *(int *)ptr = color;
}