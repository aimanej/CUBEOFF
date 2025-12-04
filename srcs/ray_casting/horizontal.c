#include "../../includes/cub3d.h"

void first_hor_inter(t_map *map, t_ray *ray)
{
    ray->hor_inter_row = floor(map->player.center_pos.row / TILE_SIZE) * TILE_SIZE;
    if (ray->face_du == DOWN)
        ray->hor_inter_row += TILE_SIZE;
    double opp = 0;
    if (ray->face_du == UP)
        opp = map->player.center_pos.row - ray->hor_inter_row;
    else if (ray->face_du == DOWN)
        opp = ray->hor_inter_row - map->player.center_pos.row;
    ray->tanner = tan(ray->angle);
    double adj = opp / ray->tanner;
    if (ray->face_du == UP)
        adj *= -1;
    ray->hor_inter_col = map->player.center_pos.col + adj;
}

void hor_step_calc(t_map *map, t_ray *ray)
{
    ray->hor_row_step = TILE_SIZE;
    ray->hor_col_step = ray->hor_row_step / ray->tanner;
    if (ray->face_du == UP)
    {
        ray->hor_row_step *= -1;
    }
    if (ray->face_lr == LEFT && ray->hor_col_step > 0)
        ray->hor_col_step = -fabs(ray->hor_col_step);
    else if (ray->face_lr == RIGHT && ray->hor_col_step < 0)
        ray->hor_col_step = fabs(ray->hor_col_step);
}

void hor_distance_calc(t_map *map, t_ray *ray)
{
    double off = (ray->face_du == UP) ? -1 : 0;

    while (!wall_check(map, ray->hor_inter_row + off, ray->hor_inter_col))
    {
        ray->hor_inter_row += ray->hor_row_step;
        ray->hor_inter_col += ray->hor_col_step;
        if (ray->hor_inter_col < 0 || ray->hor_inter_col >= map->len * TILE_SIZE || ray->hor_inter_row < 0 || ray->hor_inter_row >= map->size * TILE_SIZE)
            break;
        // return;
    }
    t_player player = map->player;
    
    ray->hor_wall_distance = AB_distance(ray->hor_inter_row, ray->hor_inter_col, player.center_pos.row, player.center_pos.col);

    // printf("horizontal wall distance  %f\n", distance);
    return ;
}