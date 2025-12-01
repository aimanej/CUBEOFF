#include "../../includes/cub3d.h"

int texture_init(t_mlx *mlx)
{

    //garbage collector to be added

    t_map *map = &(mlx->map);
    map->tex_no.img_ptr = mlx_xpm_file_to_image(mlx->mlx, "/home/aijadid/Desktop/CUBEOFF/textures/149.xpm", &(map->tex_no.width), &(map->tex_no.height));
    // printf("width : %p\n",map->tex_no.img_ptr  );
    if (!map->tex_no.img_ptr)
        return 0;
    map->tex_so.img_ptr = mlx_xpm_file_to_image(mlx->mlx, "/home/aijadid/Desktop/CUBEOFF/textures/152.xpm", &(map->tex_so.width), &(map->tex_so.height));
    if (!map->tex_no.img_ptr)
        return 0;
    map->tex_ea.img_ptr = mlx_xpm_file_to_image(mlx->mlx, "/home/aijadid/Desktop/CUBEOFF/textures/153.xpm", &(map->tex_ea.width), &(map->tex_ea.height));
    if (!map->tex_no.img_ptr)
        return 0;
    map->tex_we.img_ptr = mlx_xpm_file_to_image(mlx->mlx, "/home/aijadid/Desktop/CUBEOFF/textures/176.xpm", &(map->tex_we.width), &(map->tex_we.height));
    if (!map->tex_we.img_ptr)
        return 0;
    
    map->tex_no.addr = mlx_get_data_addr(map->tex_no.img_ptr, &(map->tex_no.bpp), &(map->tex_no.line_len), &(map->tex_no.endian));
    if(!map->tex_no.addr)
        return 0;
    map->tex_so.addr = mlx_get_data_addr(map->tex_so.img_ptr, &(map->tex_so.bpp), &(map->tex_so.line_len), &(map->tex_so.endian));
    if(!map->tex_so.addr)
        return 0;
    map->tex_ea.addr = mlx_get_data_addr(map->tex_ea.img_ptr, &(map->tex_ea.bpp), &(map->tex_ea.line_len), &(map->tex_ea.endian));
    if(!map->tex_ea.addr)
        return 0;
    map->tex_we.addr = mlx_get_data_addr(map->tex_we.img_ptr, &(map->tex_we.bpp), &(map->tex_we.line_len), &(map->tex_we.endian));
    if(!map->tex_we.addr)
        return 0;
    return 1;

}