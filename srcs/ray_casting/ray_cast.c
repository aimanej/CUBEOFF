#include "../../includes/cub3d.h"

void ray_cast(t_map *map)
{
    set_ray_angles(map);
    distance_prep(map);
    texture_col_int(map);
    draw_walls(map);
}

void distance_prep(t_map *map)
{
    int t = 0;
    while (map->ray_arr[t])
    {
        first_hor_inter(map, map->ray_arr[t]);
        hor_step_calc(map, map->ray_arr[t]);
        first_ver_inter(map, map->ray_arr[t]);
        ver_step_calc(map, map->ray_arr[t]);
        hor_distance_calc(map, map->ray_arr[t]);
        ver_distance_calc(map, map->ray_arr[t]);
        set_nearest_wall(map, map->ray_arr[t]);
        set_compass(map, map->ray_arr[t]);
        projected_wall_height(map, map->ray_arr[t]);
        t++;
    }
}

void draw_walls(t_map *map)
{
    int t = 0;
    int cur_col = 0;
    double step = 0;
    while (map->ray_arr[t])
    {
        t_ray *ray = map->ray_arr[t];
        paint_ceiling(map, ray, cur_col);
        paint_wall(map, ray, cur_col);
        paint_floor(map, ray, cur_col);
        t++;
        cur_col++;
    }
}
