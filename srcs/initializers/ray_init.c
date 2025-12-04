#include "../../includes/cub3d.h"

t_ray *newray()
{
    t_ray *ray;

    // ray = malloc(sizeof(t_ray));
    ray = ft_malloc(sizeof(t_ray));
    if(!ray)
        return NULL;
    bzero(ray, sizeof(ray));
    ray->hor_wall_distance = INFINITY;
    ray->ver_wall_distance = INFINITY;
    ray->wall_distance = INFINITY;
    return ray;
}

int init_ray_arr(t_map *map)
{
    // map->ray_arr = malloc(sizeof(t_ray *) * (WIDTH + 1));

    map->ray_arr = ft_malloc(sizeof(t_ray *) * (WIDTH + 1));
    
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