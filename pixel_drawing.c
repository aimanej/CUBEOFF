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
    // int posx = map->player.center_pos.col;
    // int posy = map->player.center_pos.row;

    // double angle = map->player.view_angle;
    // // if (map->player.turn_dir != 0)
    // // {
    // //     angle += map->player.turn_dir * map->player.rotation_speed;
    // //     map->player.view_angle = angle;
    // // }

    // double dirx = cos(angle);
    // double diry = sin(angle);
    // for (int a = 1; a < 25; a++)
    // {
    //     double nextx = posx + dirx * a;
    //     double nexty = posy + diry * a;
    //     draw_to_img(&(map->img), nextx, nexty, chimicolor(160, 27, 12));
    // }
    t_player player = map->player;
    double angle = player.view_angle;
    double nextx = player.center_pos.col + cos(angle);
    double nexty = player.center_pos.row + sin(angle);
    int t = 1;
    while (!wall_check(map, nexty, nextx))
    {
        draw_to_img(&(map->img), nextx, nexty, chimicolor(155, 155, 155));
        nextx = player.center_pos.col + cos(angle) * t;
        nexty = player.center_pos.row + sin(angle) * t;
        // printf("%f, %f <--- positions sent\n\n", nextx, nexty);
        t++;
    }
}

void player_update(t_map *map)

{
    if (map->player.walk_dir)
    {
        double step = map->player.move_speed * map->player.walk_dir;
        double next_cx = map->player.center_pos.col + cos(map->player.view_angle) * step;
        double next_cy = map->player.center_pos.row + sin(map->player.view_angle) * step;
        int nextx = next_cx / TILE_SIZE;
        int nexty = next_cy / TILE_SIZE;
        if (map->map[nexty][nextx] == '1')
            return;
        else
        {
            map->player.center_pos.row = next_cy;
            map->player.center_pos.col = next_cx;
            map->player.pos.col = nextx;
            map->player.pos.row = nexty;
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

                        draw_to_img(&(mlx->map.img), (col * TILE_SIZE) + a, (row * TILE_SIZE) + b, chimicolor(160, 27, 12));
                    }
                }
            }
            col++;
        }
        row++;
    }
    draw_player(&(mlx->map));
    draw_line(&(mlx->map));
    cast_rays(mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->map.img.img_ptr, 0, 0);
}

int wall_check(t_map *map, double row, double col)
{
    int coll = ceil((int)col / TILE_SIZE);
    int roww = ceil((int)row / TILE_SIZE);
    // printf("coll : %d roww %d position checked : %c\n", coll, roww, map->map[roww][coll]);

    if (coll <= 0 || coll >= map->len - 1 || roww <= 0 || roww >= map->size - 1 || map->map[roww][coll] == '1')
        return 1;
    return 0;
}

double hoz_distance(t_map *map)
{
    t_ray ray = map->player.ray;
    double col_inter = 0;
    double row_inter = floor(map->player.center_pos.row / TILE_SIZE) * TILE_SIZE;
    if (map->player.face_du == DOWN)
        row_inter += TILE_SIZE;
    double opp = 0;
    if (map->player.face_du == UP)
        opp = map->player.center_pos.row - row_inter;
    else if (map->player.face_du == DOWN)
        opp = row_inter - map->player.center_pos.row;
    if (fabs(sin(map->player.view_angle)) < 0.0001)
        return 0;
    double tanner = tan(map->player.view_angle);
    printf("tan ---- > %f\n", tanner);
    double adj = opp / tanner;
    if (map->player.face_du == UP)
        adj *= -1;
    col_inter = map->player.center_pos.col + adj;
    double row_step = TILE_SIZE;
    double col_step = row_step / tanner;
    if (map->player.face_du == UP)
    {
        row_step *= -1;
    }
    if (map->player.face_lr == LEFT)
        col_step = -fabs(col_step);
    else if (map->player.face_lr == RIGHT)
        col_step = fabs(col_step);
    int coef = 0;
    double off = (map->player.face_du == UP) ? -1 : 0;
    int a = 0;
    while (!wall_check(map, row_inter + off, col_inter))
    {
        a++;
        row_inter += row_step;
        col_inter += col_step;
        if (col_inter < 0 || col_inter >= map->len * TILE_SIZE || row_inter < 0 || row_inter >= map->size * TILE_SIZE)
            break;
        // return;
    }
    double distance = sqrt(((row_inter - map->player.center_pos.row) * (row_inter - map->player.center_pos.row)) + ((col_inter - map->player.center_pos.col) * (col_inter - map->player.center_pos.col)));

    printf("distance  %f\n", distance);
    return distance;
    // printf("last point drawn : %f , %f - found wall ? : %d \n", nextx, nexty, wall_check(map, nextx, nexty));
}

double ver_distance(t_map *map)
{
    t_player player = map->player;

    double row_inter = 0;
    double col_inter = floor(player.center_pos.col / TILE_SIZE) * TILE_SIZE;
    if (player.face_lr == RIGHT)
        col_inter += TILE_SIZE;
    double adj = 0;
    if (player.face_lr == RIGHT)
        adj = col_inter - player.center_pos.col;
    else if (player.face_lr == LEFT)
        adj = player.center_pos.col - col_inter;
    
    if (fabs(sin(player.view_angle)) == 1)
        return 0;
    double opp = tan(player.view_angle) * adj;
    // if (map->player.face_du == UP)
    //     opp *= -1;
    if (player.face_du == UP && player.face_lr == RIGHT)
        row_inter = player.center_pos.row - opp;
    else if (player.face_du == DOWN)
        row_inter = player.center_pos.row + opp;

    printf("checking verticals : %f %f\n", row_inter, col_inter);
    return 0;
    // printf("last point drawn : %f , %f - found wall ? : %d \n", nextx, nexty, wall_check(map, nextx, nexty));
}

void cast_rays(t_mlx *mlx)
{
    t_player *player = &(mlx->map.player);

    // hoz_distance(&(mlx->map));
    ver_distance(&(mlx->map));

    // double fov = player->fov;
    // double width = (mlx->map.len - 1) * TILE_SIZE;
    // int ray_n = width / (fov * (180 / PI));
    // double angle_step = fov / ray_n;

    // printf("")
}
