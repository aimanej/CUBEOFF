#ifndef CUB3D_H
#define CUB3D_H

#define TILE_SIZE 32
#define WIDTH 760
#define HEIGHT 480
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "/mnt/c/Users/AIMANE~1/desktop/minilibx-linux/mlx.h"
#include <strings.h>
 
#define PI 3.14159265358979323846


typedef struct s_garbage{
    void *ptr;
    int img_t;
    struct s_garbage *next;
} t_garbage;

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
    double unclipped;
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
    t_vec center_pos;
    int turn_dir;
    int walk_dir;
    int side_walk;
    double view_angle;
    int move_speed;
    double rotation_speed;
    double fov;
    t_face face_du;
    t_face face_lr;
    char player_dir;
    int player_c;
} t_player;

typedef struct s_map
{
    char **map;
    int size;
    int len;
    double screenw;
    t_image img;
    t_image textures[4];
    t_player player;
    t_ray **ray_arr;
    int fl_color;
    int ceil_color;
} t_map;

typedef struct s_mlx
{
    void *mlx;
    void *win;
    t_map map;
} t_mlx;

int chimicolor(int r, int g, int b);
void draw_to_img(t_image *img, int row, int col, int color);
void render_func(t_mlx *mlx);
void ft_add_last_ptr(t_garbage **dump, t_garbage *new);
t_garbage **dump_ptr();
t_garbage *ft_new_ptr(void *ptr, int type);
void ft_free_select(void *ptr);

// key hooks
int press_hook(int keysim, void *data);
int release_hook(int keysim, void *data);
void player_update(t_map *map);
int wall_check(t_map *map, double row, double col);
double ab_distance(double rowa, double cola, double rowb, double colb);
int chimicolor(int r, int g, int b);
double normalize_angle(double angle);
double ab_distance(double rowa, double cola, double rowb, double colb);
int getpixelcolor(t_map *map,t_ray *ray, int row, int col);
void texture_col_int(t_map *map);
int texture_init(t_mlx *mlx);
void player_direction(t_player *py);

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
void set_compass(t_map *map, t_ray *ray);
int destroy_notify(int keysim, void *data);
void mlx_hook_loops(t_mlx *mlx);

// /garbage collector
char	*ft_strdup1(char *str);
void *ft_malloc(size_t size);
void ft_free_all();

//horizontal calculations : 
void first_hor_inter(t_map *map, t_ray *ray);
void hor_step_calc(t_map *map, t_ray *ray);
void hor_distance_calc(t_map *map, t_ray *ray);

//vertical calculations : 
void ver_step_calc(t_map *map, t_ray *ray);
void first_ver_inter(t_map *map, t_ray *ray);
void ver_distance_calc(t_map *map, t_ray *ray);

void paint_ceiling(t_map *map, t_ray *ray, int cur_col);
void paint_wall(t_map *map, t_ray *ray, int cur_col);
void paint_floor(t_map *map, t_ray *ray, int cur_col);

#include "cub.h"

#endif