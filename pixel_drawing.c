#include "cub3d.h"

int chimicolor(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

// int keyhook(int keysym, void *data)
// {
//     t_cube *cube = data;
//     mlx_destroy_window(cube->mlx, cube->window);
// }

void draw_to_img(t_image *img, int x, int y, int color)
{
    char *ptr;

    ptr = img->addr + (img->line_len * y) + (x * (img->bpp / 8));
    *(int *)ptr = color;
}

void draw_player(t_map *map)
{

    double step = map->player.walk_dir * map->player.move_speed;
    int center_x = map->player.center_pos.col;
    int center_y = map->player.center_pos.row;
    int radius = map->player.radius;

    for (int dy = -radius; dy <= radius; dy++)
    {
        for (int dx = -radius; dx <= radius; dx++)
        {
            // Draw circle using distance formula
            if (dx * dx + dy * dy <= radius * radius)
            {
                draw_to_img(&(map->img), (center_x + dx) * SCALE, (center_y + dy) * SCALE, chimicolor(224, 33, 5));
            }
        }
    }
    // for(int f = 0; f <= 40; f++)
    // {
    //     int nextx = cos()
    // }
}

void draw_line(t_map *map)
{
    t_player player = map->player;
    double angle = player.view_angle;
    double nextx = player.center_pos.col + cos(angle);
    double nexty = player.center_pos.row + sin(angle);
    int t = 1;
    while (!wall_check(map, nexty, nextx))
    {
        draw_to_img(&(map->img), nextx, nexty, chimicolor(155, 155, 155));
        nextx += cos(angle);
        nexty += sin(angle);
        // printf("%f, %f <--- positions sent\n\n", nextx, nexty);
        t++;
    }
}

void drawmap(t_mlx *mlx)
{
    // t_map map = mlx->map;
    int row = 0;
    int col = 0;

    // printf("size : %d\n len : %d\n", mlx->map.size, mlx->map.len);

    while (row < mlx->map.size)
    {
        col = 0;
        while (col < mlx->map.len - 1)
        {
            if (mlx->map.map[row][col] == '1')
            {
                for (int a = 0; a < TILE_SIZE - 3; a++)
                {
                    for (int b = 0; b < TILE_SIZE - 3; b++)
                    {

                        draw_to_img(&(mlx->map.img), ((col * TILE_SIZE) + a) * SCALE, ((row * TILE_SIZE) + b) * SCALE, chimicolor(160, 27, 12));
                    }
                }
            }
            col++;
        }
        row++;
    }
    draw_player(&(mlx->map));
    // draw_line(&(mlx->map));
    mother_cast(&(mlx->map));
    // cast_rays(&(mlx->map), mlx->map.player.view_angle);
    // cast_rays(&(mlx->map), mlx->map.player.view_angle);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->map.img.img_ptr, 0, 0);
}

int wall_check(t_map *map, double row, double col)
{
    int coll = floor((int)(col / TILE_SIZE));
    int roww = floor((int)(row / TILE_SIZE));
    // printf("coll : %d roww %d position checked : %c\n", coll, roww, map->map[roww][coll]);

    if (coll <= 0 || coll >= map->len - 1 || roww <= 0 || roww >= map->size - 1 || map->map[roww][coll] == '1')
        return 1;
    return 0;
}

void one_liner(t_map *map, double distance, double angle)
{
    t_player py = map->player;

    double row_start = py.center_pos.row;
    double col_start = py.center_pos.col;

    double row_next = row_start + sin(angle);
    double col_next = col_start + cos(angle);
    double ab = AB_distance(row_start, col_start, row_next, col_next);
    // printf("distances checked : ab : %f == dis : %f \n", ab , distance);
    while (ab < distance)
    {
        if (col_next < 0 || row_next < 0 || col_next > (map->len - 1) * TILE_SIZE || row_next > map->size * TILE_SIZE)
        {
            // printf("me nigga : col : %f row %f\n", col_next, row_next);
            break;
        }
        // int rc = (int)(row_next) / TILE_SIZE;

        // if(map->map[(int)(row_next) / TILE_SIZE][(int)col_next / TILE_SIZE] == '1')
        //     break;
        // printf("col %f , col int %d \n", col_next, (int)col_next);
        draw_to_img(&(map->img), col_next * SCALE, row_next * SCALE, chimicolor(155, 155, 155));
        row_next += sin(angle);
        col_next += cos(angle);
        ab = AB_distance(row_start, col_start, row_next, col_next);
        // printf("was here:");
    }
}
void mother_cast(t_map *map)
{
    t_player py = map->player;
    double fov = py.fov;
    double screenw = (map->len - 1) * TILE_SIZE;
    double ang_start = py.view_angle - (fov / 2);
    int ray_n = screenw;
    double step = fov / ray_n;

    int t = 0;
    // printf("rys : %f current %f \n", ray_n, ang_start);
    while (ray_n > 0)
    {
        double current_ang = ang_start + step * t;
        current_ang = fmod(current_ang, 2 * PI);
        if (current_ang < 0)
            current_ang += 2 * PI;
        // current_ang = fmod(current_ang, (2 * PI));
        // double hoz = hoz_distance(map, current_ang);
        // double ver = ver_distance(map, current_ang);
        // printf("current angl : %f\n", ang_start);
        cast_rays(map, current_ang);
        // cast_rays(map, py.view_angle);
        ray_n--;
        t++;
    }
    // // printf("FOV %f angle start %f stepss %f , number of rays %f\n", fov, ang_start, step, ray_n);
}

void cast_rays(t_map *map, double angle)
{
    t_player *player = &(map->player);
    static int cur_col;

    int face_lr = 0;
    int face_du = 0;
    if (angle > (PI / 2) && angle < (3 * PI) / 2)
        face_lr = LEFT;
    else
        face_lr = RIGHT;
    if (angle >= 0 && angle <= PI)
        face_du = DOWN;
    else
        face_du = UP;

    double hoz = hoz_distance(map, angle, face_du, face_lr);
    double ver = ver_distance(map, angle, face_du, face_lr);

    // if (cur_col == ((map->len - 1) * TILE_SIZE - 1))
    printf("hoz %f , ver %f\n", hoz, ver);

    one_liner(map, (hoz < ver) ? hoz : ver, angle);

    double wall_distance = (hoz < ver) ? hoz : ver;
    double wall_hight = TILE_SIZE;

    double proj_dist = (TILE_SIZE * map->size / 2) / tan(player->fov / 2);

    double proj_height = (wall_hight / wall_distance) * proj_dist;

    if (proj_height > (TILE_SIZE * map->size) - 10)
        return;

    int row_start = ((TILE_SIZE * (map->size - 1)) / 2) - proj_height / 2;

    // printf("distance :%f  hight : %f row start %f \n", wall_distance, proj_height, row_start);
    while (proj_height > 0)
    {
        if(cur_col > map->len * TILE_SIZE || row_start > (map->size - 1) * TILE_SIZE || cur_col < 0 || row_start < 0)
            break;
        draw_to_img(&(map->img), cur_col, row_start, chimicolor(120, 120, 120));
        proj_height--;
        row_start++;
    }
    cur_col++;
    if (cur_col == (map->len - 1) * TILE_SIZE)
        cur_col = 0;

    // printf("")
}
