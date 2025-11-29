
#include "../../includes/cub3d.h"

void player_update(t_map *map)

{
    if (map->player.walk_dir)
    {
        double step = map->player.move_speed * map->player.walk_dir;
        double next_cx = map->player.center_pos.col + cos(map->player.view_angle) * step;
        double next_cy = map->player.center_pos.row + sin(map->player.view_angle) * step;
        int nextx = next_cx / TILE_SIZE;
        int nexty = next_cy / TILE_SIZE;
        if (map->map[nexty][nextx] == '1')
            return;
        else
        {
            map->player.center_pos.row = next_cy;
            map->player.center_pos.col = next_cx;
            map->player.pos.col = nextx;
            map->player.pos.row = nexty;
        }
        // printf("next positions (%d ,%d )\n", player->pos.x, player->pos.y);
    }
    if (map->player.turn_dir)
    {
        map->player.view_angle += map->player.rotation_speed * map->player.turn_dir;
        map->player.view_angle = fmod(map->player.view_angle, (2 * PI));
        if (map->player.view_angle < 0)
            map->player.view_angle = (2 * PI) + map->player.view_angle;
        if (map->player.view_angle > 0 && map->player.view_angle < PI)
            map->player.face_du = DOWN;
        else
            map->player.face_du = UP;
        if (map->player.view_angle >= (PI / 2) && map->player.view_angle <= (3 * PI / 2))
            map->player.face_lr = LEFT;
        else
            map->player.face_lr = RIGHT;
    }
}