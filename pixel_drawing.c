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
    int center_x = map->player.center_pos.row;
    int center_y = map->player.center_pos.col;
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
    int posx = map->player.center_pos.row;
    int posy = map->player.center_pos.col;

    double angle = map->player.view_angle;
    // if (map->player.turn_dir != 0)
    // {
    //     angle += map->player.turn_dir * map->player.rotation_speed;
    //     map->player.view_angle = angle;
    // }

    double dirx = cos(angle);
    double diry = sin(angle);
    for (int a = 1; a < 25; a++)
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
        double next_cx = map->player.center_pos.row + cos(map->player.view_angle) * step;
        double next_cy = map->player.center_pos.col + sin(map->player.view_angle) * step;
        int nextx = next_cx / TILE_SIZE;
        int nexty = next_cy / TILE_SIZE;
        if (map->map[nexty][nextx] == '1')
            return;
        else
        {
            map->player.center_pos.row = next_cx;
            map->player.center_pos.col = next_cy;
            map->player.pos.row = nextx;
            map->player.pos.col = nexty;
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
    int row = 0;
    int col = 0;

    // printf("size : %d\n len : %d\n", mlx->map.size, mlx->map.len);

    while (col < mlx->map.size)
    {
        row = 0;
        while (row < mlx->map.len - 1)
        {
            if (mlx->map.map[col][row] == '1')
            {
                for (int a = 0; a < TILE_SIZE - 3; a++)
                {
                    for (int b = 0; b < TILE_SIZE - 3; b++)
                    {

                        draw_to_img(&(mlx->map.img), (row * TILE_SIZE) + a, (col * TILE_SIZE) + b, chimicolor(160, 27, 12));
                    }
                }
            }
            row++;
        }
        col++;
    }
    draw_player(&(mlx->map));
    draw_line(&(mlx->map));
    cast_rays(mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->map.img.img_ptr, 0, 0);
}

int wall_check(t_map *map, double row, double col)
{
    int xx = ceil((int)row / TILE_SIZE);
    int yy = ceil((int)col / TILE_SIZE);
    // printf("xx : %d yy %d position checked : %c\n", xx, yy, map->map[yy][xx]);

    if (xx <= 0 || xx >= map->len - 1 || yy <= 0 || yy >= map->size - 1 || map->map[yy][xx] == '1')
        return 1;
    return 0;
}

void cast_one(t_map *map)
{
    t_ray ray = map->player.ray;
    double row_inter = 0;
    double col_inter = floor(map->player.center_pos.col / TILE_SIZE) * TILE_SIZE;
    if (map->player.face_du == DOWN)
        col_inter += TILE_SIZE;
    double opp = 0;
    if (map->player.face_du == UP)
        opp = map->player.center_pos.col - col_inter;
    else if (map->player.face_du == DOWN)
        opp = col_inter - map->player.center_pos.col;
    if (map->player.view_angle == PI || map->player.view_angle == PI / 2 || map->player.view_angle == 2 * PI || map->player.view_angle == (3 * PI) / 2)
    {
        printf("skipped intesection check\n");
        return;
    }
    double tanner = tan(map->player.view_angle);
    printf("tan ---- > %f\n", tanner);
    double adj = opp / tanner;
    if (map->player.face_du == UP)
        adj *= -1;
    row_inter = map->player.center_pos.row + adj;
    // if (map->player.face_lr == RIGHT)
    // {
    //     // printf("\n adding --> %d \n", offset);
    // }
    // else if (map->player.face_lr == LEFT)
    // {
    //     row_inter = map->player.center_pos.row - adj;
    //     // printf("subtracting x --> %d \n", ((map->player.center_pos.col - col_inter) / tan(map->player.view_angle)));
    // }
    printf("----->intesection x : %f y: %f\n", row_inter, col_inter);
    double col_step = TILE_SIZE;
    double row_step = col_step / tanner;
    if (map->player.face_du == UP)
    {
        col_step *= -1;
    }
    if (map->player.face_lr == LEFT)
        row_step = -fabs(row_step);
    else if (map->player.face_lr == RIGHT)
        row_step = fabs(row_step);
    printf("tan %f of %f syeps : row col %f %f \n", tanner, map->player.view_angle, row_step, col_step);

    int coef = 0;
    double off = (map->player.face_du == UP) ? -1 : 1;
    if (wall_check(map, row_inter, col_inter))
    {
        printf("wall inter with steps : %f %f\n", row_inter, col_inter + off);
        return;
    }

    while (!wall_check(map, row_inter + (row_step * coef) + 1, col_inter + (col_step * coef) + 1))
    {
        coef++;
    }
    printf("wall inter with steps : %f %f coef  %d \n", row_inter + (row_step * coef) + 1, col_inter + (col_step * coef) + 1, coef);

    // //casting ray for precision check
    // t_player player = map->player;
    // double angle = player.view_angle;
    // double nextx = player.center_pos.row + cos(angle);
    // double nexty = player.center_pos.col + sin(angle);
    // int t = 1;
    // while (!wall_check(map, nextx, nexty))
    // {
    //     draw_to_img(&(map->img), nextx, nexty, chimicolor(155, 155, 155));
    //     nextx = player.center_pos.row + cos(angle) * t;
    //     nexty = player.center_pos.col + sin(angle) * t;
    //     // printf("%f, %f <--- positions sent\n\n", nextx, nexty);
    //     t++;
    // }
    // printf("last point drawn : %f , %f - found wall ? : %d \n", nextx, nexty, wall_check(map, nextx, nexty));
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
