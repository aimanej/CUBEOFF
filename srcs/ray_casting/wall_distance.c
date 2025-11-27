#include "../../includes/cub3d.h"



double hoz_distance(t_map *map, double view_angle, int face_du, int face_lr)
{
    // t_ray ray = map->player.ray;
    // first horizontal intersection
    double col_inter = 0;
    double row_inter = floor(map->player.center_pos.row / TILE_SIZE) * TILE_SIZE;
    if (face_du == DOWN)
        row_inter += TILE_SIZE;
    double opp = 0;
    if (face_du == UP)
        opp = map->player.center_pos.row - row_inter;
    else if (face_du == DOWN)
        opp = row_inter - map->player.center_pos.row;
    if (fabs(sin(view_angle)) < 0.0001)
        return INFINITY;
    double tanner = tan(view_angle);
    // printf("tan ---- > %f\n", tanner);
    double adj = opp / tanner;
    if (face_du == UP)
        adj *= -1;
    col_inter = map->player.center_pos.col + adj;

    // step calculation
    double row_step = TILE_SIZE;
    double col_step = row_step / tanner;
    if (face_du == UP)
    {
        row_step *= -1;
    }
    if (face_lr == LEFT && col_step > 0)
        col_step = -fabs(col_step);
    else if (face_lr == RIGHT && col_step < 0)
        col_step = fabs(col_step);

    //wall check
    int coef = 0;
    double off = (face_du == UP) ? -1 : 0;
    int a = 0;

    // ray to wall inter
    while (!wall_check(map, row_inter + off, col_inter))
    {
        a++;
        row_inter += row_step;
        col_inter += col_step;
        if (col_inter < 0 || col_inter >= map->len * TILE_SIZE || row_inter < 0 || row_inter >= map->size * TILE_SIZE)
            break;
        // return;
    }
    t_player player = map->player;
    double distance = AB_distance(row_inter, col_inter, player.center_pos.row, player.center_pos.col);

    // printf("horizontal wall distance  %f\n", distance);
    return distance;
    // printf("last point drawn : %f , %f - found wall ? : %d \n", nextx, nexty, wall_check(map, nextx, nexty));
}

double AB_distance(double rowa, double cola, double rowb, double colb)
{
    return sqrt(((rowa - rowb) * (rowa - rowb)) + ((cola - colb) * (cola - colb)));
}

double ver_distance(t_map *map, double view_angle, int face_du, int face_lr)
{
    t_player player = map->player;

    //first vertical intersection 

    double row_inter = 0;
    double col_inter = floor(player.center_pos.col / TILE_SIZE) * TILE_SIZE;
    if (face_lr == RIGHT)
        col_inter += TILE_SIZE;
    double adj = 0;
    if (face_lr == RIGHT)
        adj = col_inter - player.center_pos.col;
    else if (face_lr == LEFT)
        adj = player.center_pos.col - col_inter;

    if (fabs(cos(view_angle)) < 0.0001)
        return INFINITY;
    // if (map->player.face_du == UP)
    //     adj *= -1;
    double opp = fabs(tan(view_angle) * adj);
    if (face_du == UP)
        row_inter = player.center_pos.row - opp;
    else if (face_du == DOWN)
        row_inter = player.center_pos.row + opp;
        
        ///step calculaction 

    double col_step = TILE_SIZE;
    double row_step = tan(view_angle) * TILE_SIZE;
    if (face_lr == LEFT)
        col_step *= -1;
    if (face_du == UP)
        row_step = -fabs(row_step);
    else if (face_du == DOWN)
        row_step = fabs(row_step);

    //distance calculation 
    
    int coef = 0;
    double off = (face_lr == LEFT) ? -1 : 0;
    int a = 0;
    while (!wall_check(map, row_inter, col_inter + off))
    {
        a++;
        row_inter += row_step;
        col_inter += col_step;
        if (col_inter < 0 || col_inter >= map->len * TILE_SIZE || row_inter < 0 || row_inter >= map->size * TILE_SIZE)
            break;
        // return;
    }
    double distance = AB_distance(row_inter, col_inter, player.center_pos.row, player.center_pos.col);
    // printf("vertical wall distance : %f\n", distance);
    return distance;
    // printf("last point drawn : %f , %f - found wall ? : %d \n", nextx, nexty, wall_check(map, nextx, nexty));
}