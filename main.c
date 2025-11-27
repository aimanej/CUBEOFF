#include "includes/cub3d.h"
// #include "/home/aimane-jadid/Desktop/minilibx-linux/mlx.h"

void get_player_pos(t_map *map)
{
    int row = 0;
    int col = 0;
    while (map->map[row])
    {
        col = 0;
        while (map->map[row][col])
        {
            if (map->map[row][col] == 'N')
            {
                map->player.pos.row = row;
                map->player.pos.col = col;
                map->player.center_pos.row = row * TILE_SIZE + (TILE_SIZE / 2);
                map->player.center_pos.col = col * TILE_SIZE + (TILE_SIZE / 2);
            }
            col++;
        }
        row++;
    }
}

void intializer(t_mlx *mlx)
{
    mlx->map.player.move_speed = 2;
    mlx->map.player.pos.row = 0;
    mlx->map.player.pos.col = 0;
    mlx->map.player.radius = 3;
    mlx->map.player.rotation_speed = 2 * (PI / 180);
    mlx->map.player.view_angle = 0 * (PI / 180);
    if (mlx->map.player.view_angle > 0 && mlx->map.player.view_angle < PI)
        mlx->map.player.face_du = DOWN;
    else
        mlx->map.player.face_du = UP;
    if (mlx->map.player.view_angle > (PI / 2) && mlx->map.player.view_angle < (3 * PI / 2))
        mlx->map.player.face_lr = LEFT;
    else
        mlx->map.player.face_lr = RIGHT;
    mlx->map.player.center_pos.row = 0;
    mlx->map.player.center_pos.col = 0;
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
t_ray *newray()
{
    t_ray *ray;

    ray = malloc(sizeof(t_ray));
    if(!ray)
        return NULL;
    ray->angle = 0;
    ray->hor_inter_row = 0;
    ray->hor_inter_col = 0;
    ray->hor_row_step = 0;
    ray->hor_col_step = 0;
    ray->wallhit_row = 0;
    ray->wallhit_col = 0;
    ray->ver_inter_row = 0;
    ray->ver_inter_col = 0;
    ray->ver_row_step = 0;
    ray->ver_col_step = 0;
    ray->hor_wall_distance = 0;
    ray->ver_wall_distance = 0;
    ray->wall_distance = 0;
    ray->face_lr = 0;
    ray->face_du = 0;
    ray->tanner = 0;
    ray->wall_height = 0;
    ray->row_start = 0;
    ray->row_end = 0;
    return ray;
}

int init_ray_arr(t_map *map)
{
    map->ray_arr = malloc(sizeof(t_ray *) * (WIDTH + 1));
    if(!(map->ray_arr))
        return 0;
    int t = 0;
    while(t < WIDTH)
    {
        map->ray_arr[t] = newray();
        t++;
    }
    map->ray_arr[t] = NULL;
    return 1;
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
    mlx.map.len = ft_strlen(mlx.map.map[0]) - 1;
    mlx.map.screenw = (mlx.map.len) * TILE_SIZE;
    mlx.mlx = mlx_init();
    // mlx.win = mlx_new_window(mlx.mlx, TILE_SIZE * (ft_strlen(mlx.map.map[0]) - 1), mlx.map.size * TILE_SIZE, "WINDOW");
    mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "WINDOW");
    init_ray_arr(&(mlx.map));
    // ray_cast(&(mlx.map));
    int x = 0;

    mlx.map.img.img_ptr = mlx_new_image(mlx.mlx, TILE_SIZE * ft_strlen(mlx.map.map[0]), mlx.map.size * TILE_SIZE);
    mlx.map.img.addr = mlx_get_data_addr(mlx.map.img.img_ptr, &(mlx.map.img.bpp), &(mlx.map.img.line_len), &(mlx.map.img.endian));

    // texture

    // int height = 153;
    // int width = 234;

    // mlx.map.texture.img_ptr = mlx_xpm_file_to_image(mlx.mlx, "/home/aijadid/Desktop/CUBEOFF/text.xpm", &width, &height);
    // mlx.map.texture.addr = mlx_get_data_addr(mlx.map.texture.img_ptr, &(mlx.map.texture.bpp), &(mlx.map.texture.line_len), &(mlx.map.texture.endian));
    // // printf("position %d\n %d\n", mlx.map.player.pos.x,mlx.map.player.pos.y );
    drawmap(&mlx);
    // mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.map.img.img_ptr, 0, 0);

    // mlx_key_hook(mlx.win, &hooker, &mlx);
    mlx_hook(mlx.win, 2, (1L << 0), (int (*)())press_hook, &mlx);
    mlx_hook(mlx.win, 3, (1L << 1), (int (*)())release_hook, &mlx);
    mlx_loop_hook(mlx.mlx, (int (*)())gameloop, &mlx);
    // mlx_hook()
    mlx_loop(mlx.mlx);
    mlx_destroy_window(mlx.mlx, mlx.win);
    mlx_destroy_display(mlx.mlx);
}