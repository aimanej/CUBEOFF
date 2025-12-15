#include "../../includes/cub3d.h"

int gameloop(void *data)
{
    t_mlx *mlx = data;

    player_update(&(mlx->map));
    if (mlx->map.player.turn_dir || mlx->map.player.walk_dir || mlx->map.player.side_walk)
    {
        render_func(mlx);
    }
}
