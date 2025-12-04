#include "includes/cub3d.h"




int main(int ac,char **av)
{
    (void) ac;
    t_mlx mlx;
    // t_map map = mlx.map;
    // mlx.map.size = 0;
    map_init(&mlx);
    t_player *pla = &(mlx.map.player);
    parsing(av, &(mlx.map));
    mlx.map.len = ft_strlen(mlx.map.map[0]) - 1;    
    mlx.map.screenw = WIDTH;
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "WINDOW");
    init_ray_arr(&(mlx.map));
    texture_init(&(mlx));

    // texture
    render_func(&mlx);

    mlx_hook(mlx.win, 2, (1L << 0), (int (*)())press_hook, &mlx);
    mlx_hook(mlx.win, 3, (1L << 1), (int (*)())release_hook, &mlx);
    mlx_loop_hook(mlx.mlx, (int (*)())gameloop, &mlx);
    // mlx_hook()
    mlx_loop(mlx.mlx);
    mlx_destroy_window(mlx.mlx, mlx.win);
    mlx_destroy_display(mlx.mlx);
}