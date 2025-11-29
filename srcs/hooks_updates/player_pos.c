#include "../../includes/cub3d.h"

void get_player_pos(t_map *map)
{
    int row = 0;
    int col = 0;
    while (map->map[row])
    {
        col = 0;
        while (map->map[row][col])
        {
            if (map->map[row][col] == 'N')
            {
                map->player.pos.row = row;
                map->player.pos.col = col;
                map->player.center_pos.row = row * TILE_SIZE + (TILE_SIZE / 2);
                map->player.center_pos.col = col * TILE_SIZE + (TILE_SIZE / 2);
            }
            col++;
        }
        row++;
    }
}