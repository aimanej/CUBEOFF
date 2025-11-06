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
    int center_x = map->player.center_pos.x;
    int center_y = map->player.center_pos.y;
    int radius = map->player.radius;

    for (int dy = -radius; dy <= radius; dy++)
    {
        for (int dx = -radius; dx <= radius; dx++)
        {
            // Draw circle using distance formula
            if (dx * dx + dy * dy <= radius * radius)
            {
                draw_to_img(&(map->img), center_x + dx, center_y + dy, chimicolor(224, 33, 5));
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
    int posx = map->player.center_pos.x;
    int posy = map->player.center_pos.y;

    double angle = map->player.view_angle;
    // if (map->player.turn_dir != 0)
    // {
    //     angle += map->player.turn_dir * map->player.rotation_speed;
    //     map->player.view_angle = angle;
    // }

    double dirx = cos(angle);
    double diry = sin(angle);
    for (int a = 1; a < 60; a++)
    {
        double nextx = posx + dirx * a;
        double nexty = posy + diry * a;
        draw_to_img(&(map->img), nextx, nexty, chimicolor(160, 27, 12));
    }
}

void player_update(t_map *map)

{
    if (map->player.walk_dir)
    {
        double step = map->player.move_speed * map->player.walk_dir;
        double next_cx = map->player.center_pos.x + cos(map->player.view_angle) * step;
        double next_cy = map->player.center_pos.y + sin(map->player.view_angle) * step;
        int nextx = next_cx / TILE_SIZE;
        int nexty = next_cy / TILE_SIZE;
        if (map->map[nexty][nextx] == '1')
            return;
        else
        {
            map->player.center_pos.x = next_cx;
            map->player.center_pos.y = next_cy;
            map->player.pos.x = nextx;
            map->player.pos.y = nexty;
        }
        // printf("next positions (%d ,%d )\n", player->pos.x, player->pos.y);
    }
    if (map->player.turn_dir)
    {
        map->player.view_angle += map->player.rotation_speed * map->player.turn_dir;
        map->player.view_angle = fmod(map->player.view_angle, (2 * PI));
        if (map->player.view_angle < 0)
            map->player.view_angle = (2 * PI) + map->player.view_angle;
        if (map->player.view_angle > 0 && map->player.view_angle < PI)
            map->player.face_du = DOWN;
        else
            map->player.face_du = UP;
        if (map->player.view_angle >= (PI / 2) && map->player.view_angle <= (3 * PI / 2))
            map->player.face_lr = LEFT;
        else
            map->player.face_lr = RIGHT;
    }
}

void drawmap(t_mlx *mlx)
{
    // t_map map = mlx->map;
    int x = 0;
    int y = 0;

    printf("size : %d\n len : %d\n", mlx->map.size, mlx->map.len);

    while (x < mlx->map.size)
    {
        y = 0;
        while (y < mlx->map.len - 2)
        {
            if (mlx->map.map[x][y] == '1')
            {
                for (int a = 0; a < TILE_SIZE - 3; a++)
                {
                    for (int b = 0; b < TILE_SIZE - 3; b++)
                    {

                        draw_to_img(&(mlx->map.img), (y * TILE_SIZE) + a, (x * TILE_SIZE) + b, chimicolor(160, 27, 12));
                    }
                }
            }
            y++;
        }
        x++;
    }
    draw_player(&(mlx->map));
    draw_line(&(mlx->map));
    cast_rays(mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->map.img.img_ptr, 0, 0);
}

int wall_check(t_map *map, double x, double y, int step)
{
    int xx = (map->player.center_pos.x) + (x * step);
    int yy = map->player.center_pos.y + (y * step);
    if (map->map[xx / TILE_SIZE][yy / TILE_SIZE] == 1)
        return 1;
    return 0;
}

void cast_one(t_map *map)
{
    t_ray ray = map->player.ray;
    int x_inter = 0;
    int y_inter = floor(map->player.center_pos.y / TILE_SIZE) * TILE_SIZE;
    if (map->player.face_du == DOWN)
        y_inter += TILE_SIZE;
    if (map->player.face_lr == RIGHT)
    {
        x_inter = map->player.center_pos.x + ((map->player.center_pos.y - y_inter) / tan(map->player.view_angle));
        printf("\n adding --> %d \n", ((map->player.center_pos.y - y_inter) / tan(map->player.view_angle)));
    }
    else if (map->player.face_lr == LEFT)
    {
        x_inter = map->player.center_pos.x - ((map->player.center_pos.y - y_inter) / tan(map->player.view_angle));
        printf("subtracting x --> %d \n", ((map->player.center_pos.y - y_inter) / tan(map->player.view_angle)));
    }
    printf("intesection x : %d y: %d\n", x_inter, y_inter);
    printf(" direction up down : %d\n direction left right : %d\n ", map->player.face_du, map->player.face_lr);

    t_player player = map->player;
    for (int a = 0; a < 60; a++)
    {
        double nextx = player.center_pos.x + cos(player.view_angle) * a;
        double nexty = player.center_pos.y + sin(player.view_angle) * a;
        draw_to_img(&(map->img), nextx, nexty, chimicolor(112, 43, 66));
    }
}

void cast_rays(t_mlx *mlx)
{
    t_player *player = &(mlx->map.player);

    cast_one(&(mlx->map));
    // int t = (player->view_angle * 180) / PI;
    // printf("vie angle %d \n", t);

    // int rays = TILE_SIZE * mlx->map.len / 10;
    // int screen_width = TILE_SIZE * mlx->map.len;

    // double angle_step = player->fov / rays;

    // double current_angle = player->view_angle - (player->fov / 2);
    // double end = player->view_angle + (player->fov / 2);

    // // printf("%d step \n", (int)angle_step);
    // for(int a = 0; a < rays; a++)
    // {
    //     current_angle += angle_step;
    //     // if(current_angle > end)
    //     //     continue;
    //     for(int t = 0; t < 100; t++)
    //     {
    //         double nextx = player->center_pos.x + cos(current_angle) * t;
    //         double nexty = player->center_pos.y + sin(current_angle) * t;
    //         draw_to_img(&(mlx->map.img), nextx, nexty, chimicolor(100, 100, 100));
    //     }
    // }
}
