#include "../../includes/cub3d.h"


int chimicolor(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

// int shader(int rgb, )


void draw_to_img(t_image *img, int row, int col, int color)
{
    char *ptr;

    ptr = img->addr + (img->line_len * row) + (col * (img->bpp / 8));
    *(int *)ptr = color;
}


