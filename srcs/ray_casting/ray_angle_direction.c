#include "../../includes/cub3d.h"

void	set_ray_angles(t_map *map)
{
	t_player	player;
	double		fov;
	double		angle_start;
	double		step;
	int			t;

	player = map->player;
	fov = player.fov;
	angle_start = player.view_angle - (fov / 2);
	step = fov / map->screenw;
	t = 0;
	while (map->ray_arr[t])
	{
		map->ray_arr[t]->angle = angle_start + (step * t);
		map->ray_arr[t]->angle = normalize_angle(map->ray_arr[t]->angle);
		ray_direction(map->ray_arr[t]);
		t++;
	}
}

void	set_compass(t_map *map, t_ray *ray)
{
	if (ray->face_du == UP && (ray->hor_wall_distance < ray->ver_wall_distance))
	{
		ray->compass = NO;
	}
	if (ray->face_du == DOWN
		&& (ray->hor_wall_distance < ray->ver_wall_distance))
		ray->compass = SO;
	if ((ray->hor_wall_distance > ray->ver_wall_distance)
		&& ray->ver_inter_col > map->player.center_pos.col)
		ray->compass = EA;
	if ((ray->hor_wall_distance > ray->ver_wall_distance)
		&& ray->ver_inter_col < map->player.center_pos.col)
		ray->compass = WE;
}
