#include "../../includes/cub3d.h"

void set_nearest_wall(t_map *map, t_ray *ray)
{
    if (ray->hor_wall_distance < ray->ver_wall_distance)
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
    if (ray->wall_distance < 10)
        ray->wall_distance = 10;
}


void projected_wall_height(t_map *map, t_ray *ray)
{
    double wall_hight;
    double proj_dist;

    wall_hight = TILE_SIZE;
    proj_dist = ((WIDTH) / 2) / tan(map->player.fov / 2);
    ray->wall_height = (wall_hight / ray->wall_distance) * proj_dist;
    ray->unclipped = ray->wall_height;
    if (ray->wall_height >= HEIGHT - 1)
        ray->wall_height = HEIGHT - 1;
    ray->row_start = (HEIGHT / 2) - ray->wall_height / 2;
    if (ray->row_start < 0)
        ray->row_start = 0;
    ray->row_end = ray->row_start + ray->wall_height;
    if (ray->row_end > HEIGHT - 1)
        ray->row_end = HEIGHT - 1;
}
