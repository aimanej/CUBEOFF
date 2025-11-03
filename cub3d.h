#ifndef CUB3D_H
#define CUB3D_H

#include "get_next_line.h"
#define TILE_SIZE 100
// #define 
#include <math.h>
#include <stdio.h>
#define PI 3.14159265358979323846

typedef struct t_image{
    void *img_ptr;
    char *addr;
    int bpp;
    int line_len;
    int endian;
}t_image;

typedef struct s_vec{
    int x;
    int y;
}t_vec;

typedef struct s_player{
    t_vec pos;
    t_vec center_pos;
    int radius;
    int turn_dir;
    int walk_dir;
    double rot_angle;
    int move_speed;
    double rotation_speed;
}t_player;

typedef struct s_map{
    char **map;
    int size;
    int len;
    t_image img;
    t_player player;
}t_map;

typedef struct s_mlx{
    void *mlx;
    void *win;
    t_map map;
}t_mlx;

char	**parsing(t_map *map_s, char *av);
int	map_height(t_map *map_s, char *av);

int chimicolor(int r, int g, int b);
void draw_to_img(t_image *img, int x, int y, int color);
void drawmap(t_mlx *mlx);

#endif