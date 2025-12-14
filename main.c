#include "includes/cub3d.h"


void destroy_images(t_mlx *mlx)
{
    int t = 0;
    t_map *map = &(mlx->map);
    while(t <= 3)
    {
        mlx_destroy_image(mlx->mlx, map->textures[t].img_ptr);
        t++;
    }
    mlx_destroy_image(mlx->mlx, map->img.img_ptr);
}

void mlx_hook_loops(t_mlx *mlx)
{
    mlx_hook(mlx->win, 2, (1L << 0), (int (*)())press_hook, mlx);
    mlx_hook(mlx->win, 3, (1L << 1), (int (*)())release_hook, mlx);
    mlx_loop_hook(mlx->mlx, (int (*)())gameloop, mlx);
    mlx_loop(mlx->mlx);
}

int main(int ac,char **av)
{
    (void) ac;
    t_mlx mlx;
    mlx.mlx = mlx_init();
    printf("mlx in main address : %p\n", mlx.mlx);
    ft_add_last_ptr(dump_ptr(), ft_new_ptr(mlx.mlx, 0));
    map_init(&mlx);
    t_player *pla = &(mlx.map.player);
    parsing(av, &(mlx.map));
    mlx.map.len = ft_strlen(mlx.map.map[0]) - 1;    
    mlx.map.screenw = WIDTH;
    mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "WINDOW");
    init_ray_arr(&(mlx.map));
    texture_init(&(mlx));
    render_func(&mlx);
    mlx_hook_loops(&mlx);
    // mlx_destroy_image(mlx.mlx, mlx.map.img.img_ptr);
    mlx_destroy_window(mlx.mlx, mlx.win);
    mlx_destroy_display(mlx.mlx);
    ft_free_all(1);    
}
