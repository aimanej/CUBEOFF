#include "cub3d.h"
#include "/home/aimane-jadid/Desktop/minilibx-linux/mlx.h"

int hooker(int keysim, void *data)
{
    t_mlx *mlx = data;
    if (keysim == 65307)
    {

        mlx_loop_end(mlx->mlx);
    }
    // if(keysim == 65361)
    // {
    //     mlx->map.player
    // }
    // printf("%d\n", keysim);
    return 0;
}

void draw_player(t_map *map)
{
    // double step =
    // if (map->player.walk_dir != 0)
    // {
    //     map->player.pos.x += map->player.walk_dir * map->player.move_speed;
    //     map->player.pos.y += map->player.walk_dir * map->player.move_speed;
    //     // map->player.pos.x = center_x / TILE_SIZE - TILE_SIZE / 2;
    //     // map->player.pos.y = center_y / TILE_SIZE - TILE_SIZE / 2;
    // }
    double step = map->player.walk_dir * map->player.move_speed;
    int center_x = map->player.center_pos.x;
    int center_y = map->player.center_pos.y;
    if (map->player.walk_dir != 0)
    {
        center_x += cos(map->player.rot_angle) * step;
        center_y += sin(map->player.rot_angle) * step;
        map->player.center_pos.x = center_x ;
        map->player.center_pos.y= center_y;

        // map->player.pos.x = center_x / TILE_SIZE - TILE_SIZE / 2;
        // map->player.pos.y = center_y / TILE_SIZE - TILE_SIZE / 2;
    }

    int radius = map->player.radius;

    printf("Player center: %d, %d\n", center_x, center_y);

    for (int dy = -radius; dy <= radius; dy++)
    {
        for (int dx = -radius; dx <= radius; dx++)
        {
            // Draw circle using distance formula
            if (dx * dx + dy * dy <= radius * radius)
            {
                draw_to_img(&(map->img), center_x + dx, center_y + dy,
                            chimicolor(224, 33, 5));
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
    int posx = map->player.pos.x * TILE_SIZE + (TILE_SIZE / 2);
    int posy = map->player.pos.y * TILE_SIZE + (TILE_SIZE / 2);

    double angle = map->player.rot_angle;
    if (map->player.turn_dir != 0)
    {
        angle += map->player.turn_dir * map->player.rotation_speed;
        map->player.rot_angle = angle;
    }

    double dirx = cos(angle);
    double diry = sin(angle);
    for (int a = 1; a < 60; a++)
    {
        double nextx = posx + dirx * a;
        double nexty = posy + diry * a;
        draw_to_img(&(map->img), nextx, nexty, chimicolor(160, 27, 12));
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
                for (int a = 0; a < 95; a++)
                {
                    for (int b = 0; b < 95; b++)
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
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->map.img.img_ptr, 0, 0);
}

void get_player_pos(t_map *map)
{
    int x = 0;
    int y = 0;
    while (map->map[x])
    {
        y = 0;
        while (map->map[x][y])
        {
            if (map->map[x][y] == 'N')
            {
                map->player.pos.x = y;
                map->player.pos.y = x;
                map->player.center_pos.x = y * TILE_SIZE + (TILE_SIZE / 2);
                map->player.center_pos.y = x * TILE_SIZE + (TILE_SIZE / 2);
            }
            y++;
        }
        x++;
    }
}

void intializer(t_mlx *mlx)
{
    mlx->map.player.move_speed = 2;
    mlx->map.player.pos.x = 0;
    mlx->map.player.pos.y = 0;
    mlx->map.player.radius = 3;
    mlx->map.player.rotation_speed = 2 * (PI / 180);
    mlx->map.player.rot_angle = 30 * (PI / 180);
    mlx->map.player.center_pos.x = 0;
    mlx->map.player.center_pos.y = 0;
}

int press_hook(int keysim, void *data)
{
    t_mlx *mlx = data;
    if (keysim == 65361)
    {
        mlx->map.player.turn_dir = -1;
    }
    if (keysim == 65363)
    {
        mlx->map.player.turn_dir = 1;
    }
    if (keysim == 65362)
    {
        mlx->map.player.walk_dir = 1;
    }
    if (keysim == 65364)
    {
        mlx->map.player.walk_dir = -1;
    }
    if (keysim == 65307)
    {

        mlx_loop_end(mlx->mlx);
    }
    mlx_destroy_image(mlx->mlx, mlx->map.img.img_ptr);
    mlx->map.img.img_ptr = mlx_new_image(mlx->mlx, TILE_SIZE * ft_strlen(mlx->map.map[0]), mlx->map.size * TILE_SIZE);
    mlx->map.img.addr = mlx_get_data_addr(mlx->map.img.img_ptr, &(mlx->map.img.bpp), &(mlx->map.img.line_len), &(mlx->map.img.endian));
    drawmap(mlx);
}

int release_hook(int keysim, void *data)
{
    t_mlx *mlx = data;
    if (keysim == 65361)
    {
        mlx->map.player.turn_dir = 0;
    }
    if (keysim == 65363)
    {
        mlx->map.player.turn_dir = 0;
    }
    if (keysim == 65362)
    {
        mlx->map.player.walk_dir = 0;
    }
    if (keysim == 65364)
    {
        mlx->map.player.walk_dir = 0;
    }
}

int main()
{
    t_mlx mlx;
    // t_map map = mlx.map;
    // mlx.map.size = 0;
    intializer(&mlx);
    t_player *pla = &(mlx.map.player);
    // pla->pos.x = 0;
    // pla->pos.y = 0;
    // pla->radius = 3;
    // pla->rot_angle = 0;

    mlx.map.map = parsing(&(mlx.map), "map.txt");
    get_player_pos(&(mlx.map));
    mlx.map.len = ft_strlen(mlx.map.map[0]);
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, TILE_SIZE * (ft_strlen(mlx.map.map[0]) - 1), mlx.map.size * TILE_SIZE, "WINDOW");

    int x = 0;

    mlx.map.img.img_ptr = mlx_new_image(mlx.mlx, TILE_SIZE * ft_strlen(mlx.map.map[0]), mlx.map.size * TILE_SIZE);
    mlx.map.img.addr = mlx_get_data_addr(mlx.map.img.img_ptr, &(mlx.map.img.bpp), &(mlx.map.img.line_len), &(mlx.map.img.endian));

    // printf("position %d\n %d\n", mlx.map.player.pos.x,mlx.map.player.pos.y );
    drawmap(&mlx);
    // mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.map.img.img_ptr, 0, 0);
    // while (map.map[x])
    // {
    //     printf("%s\n", map.map[x]);
    //     x++;
    // }
    mlx_key_hook(mlx.win, &hooker, &mlx);
    mlx_hook(mlx.win, 2, (1L << 0), press_hook, &mlx);
    mlx_hook(mlx.win, 3, (1L << 1), press_hook, &mlx);

    // mlx_hook()
    mlx_loop(mlx.mlx);
    mlx_destroy_window(mlx.mlx, mlx.win);
    mlx_destroy_display(mlx.mlx);
}