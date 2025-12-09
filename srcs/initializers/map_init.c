#include "../../includes/cub3d.h"

void map_init(t_mlx *mlx)
{
    bzero(&(mlx->map), sizeof(mlx->map));
    mlx->map.player.move_speed = 2;
    mlx->map.player.radius = 3;
    mlx->map.player.rotation_speed = 2 * (PI / 180);
    mlx->map.player.fov = 60 * (PI / 180);
}