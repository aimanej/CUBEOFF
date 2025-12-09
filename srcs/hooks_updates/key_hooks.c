#include "../../includes/cub3d.h"

int press_hook(int keysim, void *data)
{
    t_mlx *mlx = data;
    if (keysim == 65361)
    {
        mlx->map.player.turn_dir = -1;
    }
    else if (keysim == 65363)
    {
        mlx->map.player.turn_dir = 1;
    }
    else if (keysim == 65362)
    {
        mlx->map.player.walk_dir = 1;
    }
    else if (keysim == 65364)
    {
        mlx->map.player.walk_dir = -1;
    }
    else if (keysim == 65307)
    {

        mlx_loop_end(mlx->mlx);
        printf("made it here\n");
        ft_free_all();
    }
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