#include "../../includes/cub3d.h"

void minimap(t_mlx *mlx)
{
    int row = 0;
    int col = 0;

    while (row < mlx->map.size)
    {
        col = 0;
        while (col < mlx->map.len - 1)
        {
            if (mlx->map.map[row][col] == '1')
            {
                for (int a = 0; a < TILE_SIZE - 3; a++)
                {
                    for (int b = 0; b < TILE_SIZE - 3; b++)
                    {

                        draw_to_img(&(mlx->map.img),  ((row * TILE_SIZE) + b) * SCALE, ((col * TILE_SIZE) + a) * SCALE, chimicolor(160, 27, 12));
                    }
                }
            }
            if (mlx->map.map[row][col] == '0' || mlx->map.map[row][col] == 'N')
            {
                for (int a = 0; a < TILE_SIZE - 3; a++)
                {
                    for (int b = 0; b < TILE_SIZE - 3; b++)
                    {

                        draw_to_img(&(mlx->map.img), ((row * TILE_SIZE) + b) * SCALE, ((col * TILE_SIZE) + a) * SCALE, chimicolor(120, 7, 12));
                    }
                }
            }
            col++;
        }
        row++;
    }
}

void draw_player(t_map *map)
{

    double step = map->player.walk_dir * map->player.move_speed;
    int center_x = map->player.center_pos.col;
    int center_y = map->player.center_pos.row;
    int radius = map->player.radius;

    for (int dy = -radius; dy <= radius; dy++)
    {
        for (int dx = -radius; dx <= radius; dx++)
        {
            // Draw circle using distance formula
            if (dx * dx + dy * dy <= radius * radius)
            {
                draw_to_img(&(map->img),  (center_y + dy) * SCALE, (center_x + dx) * SCALE, chimicolor(224, 33, 5));
            }
        }
    }
}

void draw_line(t_map *map)
{
    t_player player = map->player;
    double angle = player.view_angle;
    double nextx = player.center_pos.col + cos(angle);
    double nexty = player.center_pos.row + sin(angle);
    int t = 1;
    while (!wall_check(map, nexty, nextx))
    {
        draw_to_img(&(map->img), nextx, nexty, chimicolor(155, 155, 155));
        nextx += cos(angle);
        nexty += sin(angle);
        // printf("%f, %f <--- positions sent\n\n", nextx, nexty);
        t++;
    }
}
