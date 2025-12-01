#ifndef CUB3D_H
#define CUB3D_H

#define TILE_SIZE 64
#define SCALE 0.3
#define WIDTH 1080
#define HEIGHT 720
// #define
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "/home/aijadid/Desktop/minilibx-linux/mlx.h"
 #include <strings.h>

#define PI 3.14159265358979323846

typedef struct t_image
{
    void *img_ptr;
    char *addr;
    int bpp;
    int line_len;
    int endian;
    int width;
    int height;
    char *path;
} t_image;

typedef struct s_vec
{
    double row;
    double col;
} t_vec;

typedef enum e_wall
{
    NO,
    SO,
    EA,
    WE,
} t_wall;

typedef struct s_ray
{
    double angle;
    double hor_inter_row;
    double hor_inter_col;
    double hor_row_step;
    double hor_col_step;
    double wallhit_row;
    double wallhit_col;
    double ver_inter_row;
    double ver_inter_col;
    double ver_row_step;
    double ver_col_step;
    double hor_wall_distance;
    double ver_wall_distance;
    double wall_distance;
    double texture_col;
    int face_lr;
    int face_du;
    double tanner;
    double wall_height;
    int row_start;
    int row_end;
    t_wall compass;
} t_ray;

typedef enum e_face
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
} t_face;


typedef struct s_player
{
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
    char player_dir;
} t_player;

typedef struct s_map
{
    char **map;
    int size;
    int len;
    double screenw;
    t_image img;
    t_image tex_no;
    t_image tex_so;
    t_image tex_ea;
    t_image tex_we;
    t_player player;
    t_ray **ray_arr;
} t_map;

typedef struct s_mlx
{
    void *mlx;
    void *win;
    t_map map;
} t_mlx;

// char **parsing(t_map *map_s, char *av);
int map_height(t_map *map_s, char *av);

int chimicolor(int r, int g, int b);
void draw_to_img(t_image *img, int row, int col, int color);
void render_func(t_mlx *mlx);
// void cast_rays(t_map *map, double angle);

// key hooks
int hooker(int keysim, void *data);
int press_hook(int keysim, void *data);
int release_hook(int keysim, void *data);
void player_update(t_map *map);
int wall_check(t_map *map, double row, double col);
// double hoz_distance(t_map *map, double view_angle, int face_du, int face_lr);
// double ver_distance(t_map *map, double view_angle, int face_du, int face_lr);
double AB_distance(double rowa, double cola, double rowb, double colb);
int chimicolor(int r, int g, int b);
void mother_cast(t_map *map);
double normalize_angle(double angle);
int ray_initializer(t_map *map, int ray_n);
double AB_distance(double rowa, double cola, double rowb, double colb);
int getpixelcolor(t_map *map,t_ray *ray, int row, int col);
void texture_col_int(t_map *map);
int texture_init(t_mlx *mlx);

// new
void set_ray_angles(t_map *map);
void ray_direction(t_ray *ray);
void ray_cast(t_map *map);
void set_nearest_wall(t_map *map, t_ray *ray);
void distance_prep(t_map *map);
void projected_wall_height(t_map *map, t_ray *ray);
void draw_walls(t_map *map);
void get_player_pos(t_map *map);
void map_init(t_mlx *mlx);
int init_ray_arr(t_map *map);
int gameloop(void *data);
void minimap(t_mlx *mlx);
void draw_player(t_map *map);
void mini_rays(t_map *map);
void set_compass(t_map *map, t_ray *ray);

//horizontal calculations : 
void first_hor_inter(t_map *map, t_ray *ray);
void hor_step_calc(t_map *map, t_ray *ray);
void hor_distance_calc(t_map *map, t_ray *ray);

//vertical calculations : 
void ver_step_calc(t_map *map, t_ray *ray);
void first_ver_inter(t_map *map, t_ray *ray);
void ver_distance_calc(t_map *map, t_ray *ray);
// double AB_distance(double rowa, double cola, double rowb, double colb);
#include "../parsing/cub.h"

#endif