#include "includes/cub3d.h"


int main()
{
    t_mlx mlx;
    // t_map map = mlx.map;
    // mlx.map.size = 0;
    map_init(&mlx);
    t_player *pla = &(mlx.map.player);
    mlx.map.map = parsing(&(mlx.map), "map.txt");
    get_player_pos(&(mlx.map));
    mlx.map.len = ft_strlen(mlx.map.map[0]) - 1;
    
    mlx.map.screenw = WIDTH;
    // mlx.map.screenw = (mlx.map.len - 1) * TILE_SIZE;
    mlx.mlx = mlx_init();
    // mlx.win = mlx_new_window(mlx.mlx, TILE_SIZE * (ft_strlen(mlx.map.map[0]) - 1), mlx.map.size * TILE_SIZE, "WINDOW");
    mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "WINDOW");
    init_ray_arr(&(mlx.map));
    // ray_cast(&(mlx.map));
    int x = 0;

    mlx.map.img.img_ptr = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
    mlx.map.img.addr = mlx_get_data_addr(mlx.map.img.img_ptr, &(mlx.map.img.bpp), &(mlx.map.img.line_len), &(mlx.map.img.endian));

    // texture

    int height = 0;
    int width = 0;
    
    mlx.map.texture.img_ptr = mlx_xpm_file_to_image(mlx.mlx, "/home/aimane-jadid/Desktop/studies/cube3d/text.xpm", &width, &height);
    mlx.map.texture.addr = mlx_get_data_addr(mlx.map.texture.img_ptr, &(mlx.map.texture.bpp), &(mlx.map.texture.line_len), &(mlx.map.texture.endian));
    mlx.map.tex_height = height;
    mlx.map.tex_width = width;

    printf("length %d \n", height);
    // // printf("position %d\n %d\n", mlx.map.player.pos.x,mlx.map.player.pos.y );
    render_func(&mlx);
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