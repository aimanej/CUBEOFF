#include "../../includes/cub3d.h"

t_ray *newray()
{
    t_ray *ray;

    ray = malloc(sizeof(t_ray));
    if(!ray)
        return NULL;
    ray->angle = 0;
    ray->hor_inter_row = 0;
    ray->hor_inter_col = 0;
    ray->hor_row_step = 0;
    ray->hor_col_step = 0;
    ray->wallhit_row = 0;
    ray->wallhit_col = 0;
    ray->ver_inter_row = 0;
    ray->ver_inter_col = 0;
    ray->ver_row_step = 0;
    ray->ver_col_step = 0;
    ray->hor_wall_distance = INFINITY;
    ray->ver_wall_distance = INFINITY;
    ray->wall_distance = INFINITY;
    ray->face_lr = 0;
    ray->face_du = 0;
    ray->tanner = 0;
    ray->wall_height = 0;
    ray->row_start = 0;
    ray->row_end = 0;
    ray->texture_col = 0;
    return ray;
}

int init_ray_arr(t_map *map)
{
    map->ray_arr = malloc(sizeof(t_ray *) * (WIDTH + 1));
    if(!(map->ray_arr))
        return 0;
    int t = 0;
    while(t < WIDTH)
    {
        map->ray_arr[t] = newray();
        t++;
    }
    map->ray_arr[t] = NULL;
    return 1;
}