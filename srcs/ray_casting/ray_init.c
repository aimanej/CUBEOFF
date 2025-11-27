#include "../../includes/cub3d.h"

void ray_direction(t_ray *ray)
{
    if (ray->angle > (PI / 2) && ray->angle < (3 * PI) / 2)
        ray->face_lr = LEFT;
    else
        ray->face_lr = RIGHT;
    if (ray->angle >= 0 && ray->angle <= PI)
        ray->face_du = DOWN;
    else
        ray->face_du = UP;
}

void set_ray_angles(t_map *map)
{
    t_player player = map->player;

    double fov = player.fov;
    double angle_start;
    angle_start = player.view_angle - (fov / 2);
    double step;

    step = fov / map->screenw;
    int t;

    t = 0;
    while (map->ray_arr[t])
    {
        map->ray_arr[t]->angle = angle_start + (step * t);
        ray_direction(map->ray_arr[t]);
        t++;
    }
}

void ray_cast(t_map *map)
{
    set_ray_angles(map);
    distance_prep(map);
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
        printf("wall distance : %f\n", map->ray_arr[t]->wall_distance);
        t++;
    }
}

void set_nearest_wall(t_map *map, t_ray *ray)
{
    if(ray->hor_wall_distance < ray->ver_wall_distance)
    {
        ray->wall_distance = ray->hor_wall_distance;
        ray->wallhit_col = ray->hor_inter_col;
        ray->wallhit_row = ray->hor_inter_row;
    }
    else
    {
        ray->wall_distance = ray->ver_wall_distance;
        ray->wallhit_col = ray->ver_inter_col;
        ray->wallhit_row = ray->ver_inter_row;
    }

    ray->wall_distance = ray->wall_distance * cos(ray->angle - map->player.view_angle);
    return ;
    
}



