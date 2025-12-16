#include "../../includes/cub3d.h"

void	straight_walk(t_map *map)
{
	double	step;
	double	next_cx;
	double	next_cy;
	int		nextx;
	int		nexty;

	step = map->player.move_speed * map->player.walk_dir;
	next_cx = map->player.center_pos.col + cos(map->player.view_angle) * step;
	next_cy = map->player.center_pos.row + sin(map->player.view_angle) * step;
	nextx = next_cx / TILE_SIZE;
	nexty = next_cy / TILE_SIZE;
	if (map->map[nexty][nextx] == '1')
		return ;
	else
	{
		map->player.center_pos.row = next_cy;
		map->player.center_pos.col = next_cx;
	}
}

void	side_walk(t_map *map)
{
	double	step;
	double	next_cx;
	double	next_cy;
	int		nextx;
	int		nexty;

	step = map->player.side_walk;
	next_cx = map->player.center_pos.col
		+ cos(normalize_angle(map->player.view_angle + (90 * PI / 180))) * step;
	next_cy = map->player.center_pos.row
		+ sin(normalize_angle(map->player.view_angle + (90 * PI / 180))) * step;
	nextx = next_cx / TILE_SIZE;
	nexty = next_cy / TILE_SIZE;
	if (map->map[nexty][nextx] == '1' || (map->ray_arr[WIDTH
			/ 2]->wall_distance <= (TILE_SIZE / 5)
			&& map->player.walk_dir == 1))
		return ;
	else
	{
		map->player.center_pos.row = next_cy;
		map->player.center_pos.col = next_cx;
	}
}

void	player_update(t_map *map)
{
	if (map->player.walk_dir)
		straight_walk(map);
	if (map->player.side_walk)
		side_walk(map);
	if (map->player.turn_dir)
	{
		map->player.view_angle += map->player.rotation_speed
			* map->player.turn_dir;
		map->player.view_angle = normalize_angle(map->player.view_angle);
		player_direction(&(map->player));
	}
}
