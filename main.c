#include "cub3d.h"
// #include "/home/aimane-jadid/Desktop/minilibx-linux/mlx.h"

// int hooker(int keysim, void *data)
// {
//     t_mlx *mlx = data;
//     if (keysim == 65307)
//     {

//         mlx_loop_end(mlx->mlx);
//     }
//     // if(keysim == 65361)
//     // {
//     //     mlx->map.player
//     // }
//     // printf("%d\n", keysim);
//     return 0;
// }

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
    mlx->map.player.rotation_speed = 0.5 * (PI / 180);
    mlx->map.player.view_angle = 180 * (PI / 180);
    if(mlx->map.player.view_angle > 0 && mlx->map.player.view_angle < PI)
        mlx->map.player.face_du = DOWN;
    else
        mlx->map.player.face_du = UP;
    if(mlx->map.player.view_angle > (PI / 2) && mlx->map.player.view_angle < (3 * PI / 2))
        mlx->map.player.face_lr = LEFT;
    else
        mlx->map.player.face_lr = RIGHT;
    mlx->map.player.center_pos.x = 0;
    mlx->map.player.center_pos.y = 0;
    mlx->map.player.walk_dir = 0;
    mlx->map.player.turn_dir = 0;
    mlx->map.player.fov = 60 * (PI / 180);
}

int gameloop(void *data)
{
    t_mlx *mlx = data;

    player_update(&(mlx->map));
    if (mlx->map.player.turn_dir || mlx->map.player.walk_dir)
    {
        mlx_destroy_image(mlx->mlx, mlx->map.img.img_ptr);
        mlx->map.img.img_ptr = mlx_new_image(mlx->mlx, TILE_SIZE * ft_strlen(mlx->map.map[0]), mlx->map.size * TILE_SIZE);
        mlx->map.img.addr = mlx_get_data_addr(mlx->map.img.img_ptr, &(mlx->map.img.bpp), &(mlx->map.img.line_len), &(mlx->map.img.endian));
        drawmap(mlx);
    }
}

int main()
{
    t_mlx mlx;
    // t_map map = mlx.map;
    // mlx.map.size = 0;
    intializer(&mlx);
    t_player *pla = &(mlx.map.player);
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

    // mlx_key_hook(mlx.win, &hooker, &mlx);
    mlx_hook(mlx.win, 2, (1L << 0), press_hook, &mlx);
    mlx_hook(mlx.win, 3, (1L << 1), release_hook, &mlx);
    mlx_loop_hook(mlx.mlx, gameloop, &mlx);
    // mlx_hook()
    mlx_loop(mlx.mlx);
    mlx_destroy_window(mlx.mlx, mlx.win);
    mlx_destroy_display(mlx.mlx);
}