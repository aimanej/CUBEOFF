#include "../../includes/cub3d.h"

void map_init(t_mlx *mlx)
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