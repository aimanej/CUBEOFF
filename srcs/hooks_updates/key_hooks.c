#include "../../includes/cub3d.h"


void mlx_hook_loops(t_mlx *mlx)
{
    mlx_hook(mlx->win, 2, (1L << 0), (int (*)())press_hook, mlx);
    mlx_hook(mlx->win, 3, (1L << 1), (int (*)())release_hook, mlx);
    mlx_hook(mlx->win, 17, 0, destroy_notify, NULL);
    mlx_loop_hook(mlx->mlx, (int (*)())gameloop, mlx);
    mlx_loop(mlx->mlx);
}

int destroy_notify(int keysim, void *data)
{
    ft_free_all();
}

int press_hook(int keysim, void *data)
{
    t_mlx *mlx = data;
    // printf("keysim : %d\n", keysim);
    if (keysim == 65361)
        mlx->map.player.turn_dir = -1;
    else if (keysim == 65363)
        mlx->map.player.turn_dir = 1;
    else if (keysim == 119)
        mlx->map.player.walk_dir = 1;
    else if (keysim == 115)
        mlx->map.player.walk_dir = -1;
    else if (keysim == 97)
        mlx->map.player.side_walk = -1;
    else if (keysim == 100)
        mlx->map.player.side_walk = 1;
    else if(keysim == 65505)
        mlx->map.player.move_speed *= 5;
    else if (keysim == 65307)
    {
        mlx_loop_end(mlx->mlx);
        ft_free_all();
    }
    return 0;   
}

int release_hook(int keysim, void *data)
{
    t_mlx *mlx = data;
    if (keysim == 65361)
        mlx->map.player.turn_dir = 0;
    if (keysim == 65363)
        mlx->map.player.turn_dir = 0;
    if (keysim == 119 || keysim == 115)
        mlx->map.player.walk_dir = 0;
    if(keysim == 65505)
        mlx->map.player.move_speed = 2;
    else if (keysim == 97 || keysim == 100)
        mlx->map.player.side_walk = 0;
    return 0;
}