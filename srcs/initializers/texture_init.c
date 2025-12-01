#include "../../includes/cub3d.h"

int texture_init(t_mlx *mlx)
{

    //garbage collector to be added

    t_map *map = &(mlx->map);
    map->tex1.img_ptr = mlx_xpm_file_to_image(mlx->mlx, "../../textures/149.xpm", &(map->tex1.width), &(map->tex1.height));
    if (!map->tex1.img_ptr)
        return 0;
    map->tex2.img_ptr = mlx_xpm_file_to_image(mlx->mlx, "../../textures/152.xpm", &(map->tex2.width), &(map->tex2.height));
    if (!map->tex1.img_ptr)
        return 0;
    map->tex3.img_ptr = mlx_xpm_file_to_image(mlx->mlx, "../../textures/153.xpm", &(map->tex3.width), &(map->tex3.height));
    if (!map->tex1.img_ptr)
        return 0;
    map->tex4.img_ptr = mlx_xpm_file_to_image(mlx->mlx, "../../textures/176.xpm", &(map->tex4.width), &(map->tex4.height));
    if (!map->tex4.img_ptr)
        return 0;
    
    map->tex1.addr = mlx_get_data_addr(map->tex1.img_ptr, &(map->tex1.bpp), &(map->tex1.line_len), &(map->tex1.endian));
    if(!map->tex1.addr)
        return 0;
    map->tex2.addr = mlx_get_data_addr(map->tex2.img_ptr, &(map->tex2.bpp), &(map->tex2.line_len), &(map->tex2.endian));
    if(!map->tex2.addr)
        return 0;
    map->tex3.addr = mlx_get_data_addr(map->tex3.img_ptr, &(map->tex3.bpp), &(map->tex3.line_len), &(map->tex3.endian));
    if(!map->tex3.addr)
        return 0;
    map->tex4.addr = mlx_get_data_addr(map->tex4.img_ptr, &(map->tex4.bpp), &(map->tex4.line_len), &(map->tex4.endian));
    if(!map->tex4.addr)
        return 0;
    return 1;

}