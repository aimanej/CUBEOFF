#ifndef CUB3D_H
#define CUB3D_H

#include "get_next_line.h"
#define TILE_SIZE 100
// #define 
#include <math.h>
#include <stdio.h>
#include "/home/aijadid/Desktop/minilibx-linux/mlx.h"
#define PI 3.14159265358979323846

typedef struct t_image{
    void *img_ptr;
    char *addr;
    int bpp;
    int line_len;
    int endian;
}t_image;

typedef struct s_vec{
    double row;
    double col;
}t_vec;
typedef struct s_ray{
    double angle;
    int xinter;
    int yinter;
}t_ray;

typedef enum e_face{
    UP,
    DOWN,
    LEFT,
    RIGHT,
}t_face;

typedef struct s_player{
    t_vec pos;
    t_vec center_pos;
    int radius;
    int turn_dir;
    int walk_dir;
    double view_angle;
    int move_speed;
    double rotation_speed;
    double fov;
    t_face face_du;
    t_face face_lr;
    t_ray ray;
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
void cast_rays(t_map * map, double angle);

//key hooks
int hooker(int keysim, void *data);
int press_hook(int keysim, void *data);
int release_hook(int keysim, void *data);
void player_update(t_map *map);
int wall_check(t_map *map, double row, double col);
double hoz_distance(t_map *map, double view_angle);
double ver_distance(t_map *map, double view_angle);
double AB_distance(double rowa, double cola, double rowb, double colb);
int chimicolor(int r, int g, int b);
void mother_cast(t_map *map);


#endif