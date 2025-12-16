#include "../../includes/cub3d.h"

int	wall_check(t_map *map, double row, double col)
{
	int	coll;
	int	roww;

	coll = (col / TILE_SIZE);
	roww = (row / TILE_SIZE);
	if (roww < 0 || roww >= map->size - 1 || coll <= 0
		|| coll >= ft_strlen(map->map[roww]) - 1 || map->map[roww][coll] == '1')
		return (1);
	return (0);
}

void	first_ver_inter(t_map *map, t_ray *ray)
{
	double	adj;
	double	opp;

	ray->ver_inter_row = 0;
	ray->ver_inter_col = floor(map->player.center_pos.col / TILE_SIZE)
		* TILE_SIZE;
	if (ray->face_lr == RIGHT)
		ray->ver_inter_col += TILE_SIZE;
	adj = 0;
	if (ray->face_lr == RIGHT)
		adj = ray->ver_inter_col - map->player.center_pos.col;
	else if (ray->face_lr == LEFT)
		adj = map->player.center_pos.col - ray->ver_inter_col;
	if (ray->face_du == UP)
		adj *= -1;
	opp = fabs(tan(ray->angle) * adj);
	if (ray->face_du == UP)
		ray->ver_inter_row = map->player.center_pos.row - opp;
	else if (ray->face_du == DOWN)
		ray->ver_inter_row = map->player.center_pos.row + opp;
}

void	ver_step_calc(t_map *map, t_ray *ray)
{
	ray->ver_col_step = TILE_SIZE;
	ray->ver_row_step = tan(ray->angle) * TILE_SIZE;
	if (ray->face_lr == LEFT)
		ray->ver_col_step *= -1;
	if (ray->face_du == UP)
		ray->ver_row_step = -fabs(ray->ver_row_step);
	else if (ray->face_du == DOWN)
		ray->ver_row_step = fabs(ray->ver_row_step);
}

void	ver_distance_calc(t_map *map, t_ray *ray)
{
	double	off;
	int		a;
	int		row;

	if ((ray->face_lr == LEFT))
		off = -1;
	else
		off = 0;
	a = 0;
	while (!wall_check(map, ray->ver_inter_row, ray->ver_inter_col + off))
	{
		a++;
		ray->ver_inter_row += ray->ver_row_step;
		ray->ver_inter_col += ray->ver_col_step;
		row = ray->ver_inter_row / TILE_SIZE;
		if (ray->ver_inter_row < 0 || ray->ver_inter_row >= ((map->size - 1)
				* TILE_SIZE) || ray->ver_inter_col < 0
			|| ray->ver_inter_col >= ((ft_strlen(map->map[row]) - 1)
				* TILE_SIZE))
			break ;
	}
	ray->ver_wall_distance = ab_distance(ray->ver_inter_row, ray->ver_inter_col,
			map->player.center_pos.row, map->player.center_pos.col);
	return ;
}
