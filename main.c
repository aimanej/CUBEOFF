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

int destroy_notify(int keysim, void *data)
{
    ft_free_all();
}

void mlx_hook_loops(t_mlx *mlx)
{
    mlx_hook(mlx->win, 2, (1L << 0), (int (*)())press_hook, mlx);
    mlx_hook(mlx->win, 3, (1L << 1), (int (*)())release_hook, mlx);
    mlx_hook(mlx->win, 17, 0, destroy_notify, NULL);
    mlx_loop_hook(mlx->mlx, (int (*)())gameloop, mlx);
    mlx_loop(mlx->mlx);
}

int main(int ac,char **av)
{
    (void) ac;
    t_mlx mlx;
    mlx.mlx = mlx_init();
    ft_add_last_ptr(dump_ptr(), ft_new_ptr(&mlx, 0));
    mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "WINDOW");
    map_init(&mlx);
    parsing(av, &(mlx.map));

        int colors[3] = {(mlx.map.ceil_color >> 16) & 0xFF, (mlx.map.ceil_color >> 8) & 0xFF, mlx.map.ceil_color & 0xFF};

    printf("%d, %d, %d\n", colors[0], colors[1], colors[2]);
    mlx.map.len = ft_strlen(mlx.map.map[0]) - 1;    
    mlx.map.screenw = WIDTH;
    init_ray_arr(&(mlx.map));
    texture_init(&(mlx));
    render_func(&mlx);
    mlx_hook_loops(&mlx);    
}
