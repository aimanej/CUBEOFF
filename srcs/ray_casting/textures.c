#include "../../includes/cub3d.h"

void	texture_col_int(t_map *map)
{
	int		t;
	t_ray	*ray;

	t = 0;
	while (t < WIDTH)
	{
		ray = map->ray_arr[t];
		if (ray->hor_wall_distance < ray->ver_wall_distance)
		{
			ray->texture_col = ray->wallhit_col;
		}
		else
			ray->texture_col = ray->wallhit_row;
		ray->texture_col = fmod(ray->texture_col, TILE_SIZE);
		ray->texture_col = (ray->texture_col
				* map->textures[ray->compass].width) / TILE_SIZE;
		t++;
	}
}

int	pixel_shader(t_ray *ray, int pixel)
{
	int		colors[3];
	double	shade;

	colors[0] = (pixel >> 16) & 0xFF;
	colors[1] = (pixel >> 8) & 0xFF;
	colors[2] = pixel & 0xFF;
	shade = 1 - (ray->wall_distance / 800);
	if (shade < 0.2)
		shade = 0.2;
	colors[0] *= shade;
	colors[1] *= shade;
	colors[2] *= shade;
	return (chimicolor(colors[0], colors[1], colors[2]));
}

int	getpixelcolor(t_map *map, t_ray *ray, int row, int col)
{
	char	*addr;
	int		pixel;

	if (row < 0)
		row = 0;
	if (row > map->textures[ray->compass].height)
		row = map->textures[ray->compass].height - 1;
	if (col < 0)
		col = 0;
	if (col > map->textures[ray->compass].width)
		col = map->textures[ray->compass].width - 1;
	addr = map->textures[ray->compass].addr
		+ (map->textures[ray->compass].line_len * row) + (col
			* (map->textures[ray->compass].bpp / 8));
	pixel = 0;
	if (addr)
		pixel = *(int *)addr;
	pixel = pixel_shader(ray, pixel);
	return (pixel);
}
