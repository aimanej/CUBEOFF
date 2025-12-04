#include "../../includes/cub3d.h"

int hooker(int keysim, void *data)
{
    t_mlx *mlx = data;
    printf("%d\n", keysim);
    if (keysim == 65307)
    {

        printf("made it here\n");
        ft_free_all();
        mlx_loop_end(mlx->mlx);
    }
    // if(keysim == 65361)
    // {
    //     mlx->map.player
    // }
    return 0;
}

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
    // player_update(&(mlx->map.player));
    // mlx_destroy_image(mlx->mlx, mlx->map.img.img_ptr);
    // mlx->map.img.img_ptr = mlx_new_image(mlx->mlx, TILE_SIZE * ft_strlen(mlx->map.map[0]), mlx->map.size * TILE_SIZE);
    // mlx->map.img.addr = mlx_get_data_addr(mlx->map.img.img_ptr, &(mlx->map.img.bpp), &(mlx->map.img.line_len), &(mlx->map.img.endian));
    // render_func(mlx);
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
    // player_update(&(mlx->map.player));
    // mlx_destroy_image(mlx->mlx, mlx->map.img.img_ptr);
    // mlx->map.img.img_ptr = mlx_new_image(mlx->mlx, TILE_SIZE * ft_strlen(mlx->map.map[0]), mlx->map.size * TILE_SIZE);
    // mlx->map.img.addr = mlx_get_data_addr(mlx->map.img.img_ptr, &(mlx->map.img.bpp), &(mlx->map.img.line_len), &(mlx->map.img.endian));
    // render_func(mlx);
}