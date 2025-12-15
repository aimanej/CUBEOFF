#include "../../includes/cub3d.h"

void first_ver_inter(t_map *map, t_ray *ray)
{
    ray->ver_inter_row = 0;
    ray->ver_inter_col = floor(map->player.center_pos.col / TILE_SIZE) * TILE_SIZE;
    if (ray->face_lr == RIGHT)
        ray->ver_inter_col += TILE_SIZE;
    double adj = 0;
    if (ray->face_lr == RIGHT)
        adj = ray->ver_inter_col - map->player.center_pos.col;
    else if (ray->face_lr == LEFT)
        adj = map->player.center_pos.col - ray->ver_inter_col;
    if (ray->face_du == UP)
        adj *= -1;
    double opp = fabs(tan(ray->angle) * adj);
    if (ray->face_du == UP)
        ray->ver_inter_row = map->player.center_pos.row - opp;
    else if (ray->face_du == DOWN)
        ray->ver_inter_row = map->player.center_pos.row + opp;
}

void ver_step_calc(t_map *map, t_ray *ray)
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

void ver_distance_calc(t_map *map, t_ray *ray)
{
    double off = (ray->face_lr == LEFT) ? -EPS : EPS;
    int a = 0;
    while (!wall_check(map, ray->ver_inter_row, ray->ver_inter_col + off))
    {
        a++;
        ray->ver_inter_row += ray->ver_row_step;
        ray->ver_inter_col += ray->ver_col_step;
        if (ray->ver_inter_col < 0 || ray->ver_inter_col >= map->len * TILE_SIZE || ray->ver_inter_row < 0 || ray->ver_inter_row >= map->size * TILE_SIZE)
            break;
        // return;
    }
    ray->ver_wall_distance = AB_distance(ray->ver_inter_row, ray->ver_inter_col, map->player.center_pos.row, map->player.center_pos.col);
    // printf("vertical wall distance : %f\n", distance);
    return ;
}