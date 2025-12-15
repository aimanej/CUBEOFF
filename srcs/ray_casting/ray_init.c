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

void player_direction(t_player *py)
{
    if (py->view_angle > (PI / 2) && py->view_angle < (3 * PI) / 2)
        py->face_lr = LEFT;
    else
        py->face_lr = RIGHT;
    if (py->view_angle >= 0 && py->view_angle <= PI)
        py->face_du = DOWN;
    else
        py->face_du = UP;
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
        map->ray_arr[t]->angle = normalize_angle(map->ray_arr[t]->angle);
        ray_direction(map->ray_arr[t]);
        t++;
    }
}

void ray_cast(t_map *map)
{
    set_ray_angles(map);
    distance_prep(map);
    texture_col_int(map);
    draw_walls(map);
}

void set_compass(t_map *map, t_ray *ray)
{
    if (ray->face_du == UP && (ray->hor_wall_distance < ray->ver_wall_distance))
    {
        ray->compass = NO;
    }
    if (ray->face_du == DOWN && (ray->hor_wall_distance < ray->ver_wall_distance))
        ray->compass = SO;

    if ((ray->hor_wall_distance > ray->ver_wall_distance) && ray->ver_inter_col > map->player.center_pos.col)
        ray->compass = EA;
    if ((ray->hor_wall_distance > ray->ver_wall_distance) && ray->ver_inter_col < map->player.center_pos.col)
        ray->compass = WE;
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

double AB_distance(double rowa, double cola, double rowb, double colb)
{
    return sqrt(((rowa - rowb) * (rowa - rowb)) + ((cola - colb) * (cola - colb)));
}

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
    // printf("wall distance %f \n", ray->wall_distance);
    if(ray->wall_distance < 10)
        ray->wall_distance = 10;
    return;
}

void projected_wall_height(t_map *map, t_ray *ray)
{
    double wall_hight = TILE_SIZE;

    double proj_dist = ((WIDTH) / 2) / tan(map->player.fov / 2);

    ray->wall_height = (wall_hight / ray->wall_distance) * proj_dist;
    ray->unclipped = ray->wall_height;
    // printf("unclipped : %f \n", ray->unclipped);

    // ray->wall_height /= HEIGHT;

    if (ray->wall_height >= HEIGHT - 1)
    {
        // printf("washere\n\n");
        ray->wall_height = HEIGHT - 1;
    }
    ray->row_start = (HEIGHT / 2) - ray->wall_height / 2;
    if (ray->row_start < 0)
    {
        // proj_height += row_start;
        ray->row_start = 0;
    }
    ray->row_end = ray->row_start + ray->wall_height;
    if (ray->row_end > HEIGHT - 1)
        ray->row_end = HEIGHT - 1;
    printf("wall height : %f\n", ray->wall_height);
}

void draw_walls(t_map *map)
{
    int t = 0;
    int cur_col = 0;
    double step = 0;
    while (map->ray_arr[t])
    {
        t_ray *ray = map->ray_arr[t];
        int grad = ((HEIGHT - 1) / ray->wall_height) * 4;

        step = map->textures[ray->compass].height / ray->unclipped;
        double tex_row = 0;
        if(ray->unclipped > HEIGHT)
        {
            double t = (1 - (HEIGHT / ray->unclipped)) / 2;
            // printf("t : %f height : %f \n", t, (double)(map->textures[ray->compass].height));
            tex_row = t * (double)(map->textures[ray->compass].height);
        }
        // printf("texture row : %f\n", tex_row);
        int p = 1;
        while (p < ray->row_start)
        {
            if (cur_col > WIDTH - 1 || p > HEIGHT - 1 || cur_col < 0 || p < 0)
                break;
            draw_to_img(&(map->img), p, cur_col, map->ceil_color);
            p++;
        }
        p = 0;
        // printf("wall height : %f\n", ray->wall_height);
        while (ray->row_start < ray->row_end)
        {
            if (cur_col > WIDTH - 1 || ray->row_start > HEIGHT - 1 || cur_col < 0 || ray->row_start < 0)
                break;
            int color = getpixelcolor(map, ray, tex_row, ray->texture_col);
            tex_row += step;
            draw_to_img(&(map->img), ray->row_start, cur_col, color);
            ray->row_start++;
        }
        while (ray->row_end < HEIGHT)
        {
            if (cur_col > WIDTH - 1 || ray->row_end > HEIGHT - 1 || cur_col < 0 || ray->row_end < 0)
                break;
            draw_to_img(&(map->img), ray->row_end, cur_col, map->fl_color);
            ray->row_end++;
        }
        t++;
        cur_col++;
    }
}
