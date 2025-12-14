#include "../../includes/cub3d.h"

int texture_init(t_mlx *mlx)
{


    t_map *map = &(mlx->map);
    map->textures[NO].img_ptr = mlx_xpm_file_to_image(mlx->mlx, map->textures[NO].path, &(map->textures[NO].width), &(map->textures[NO].height));
    if (!map->textures[NO].img_ptr)
        return 0;
    ft_add_last_ptr(dump_ptr(), ft_new_ptr(map->textures[NO].img_ptr, 1));
    map->textures[SO].img_ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->map.textures[SO].path, &(map->textures[SO].width), &(map->textures[SO].height));
    if (!map->textures[SO].img_ptr)
        return 0;
    ft_add_last_ptr(dump_ptr(), ft_new_ptr(map->textures[SO].img_ptr, 1));
    map->textures[EA].img_ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->map.textures[EA].path, &(map->textures[EA].width), &(map->textures[EA].height));
    if (!map->textures[EA].img_ptr)
        return 0;
    ft_add_last_ptr(dump_ptr(), ft_new_ptr(map->textures[EA].img_ptr, 1));
    map->textures[WE].img_ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->map.textures[WE].path, &(map->textures[WE].width), &(map->textures[WE].height));
    if (!map->textures[WE].img_ptr)
        return 0;
    ft_add_last_ptr(dump_ptr(), ft_new_ptr(map->textures[WE].img_ptr, 1));
    
    map->textures[NO].addr = mlx_get_data_addr(map->textures[NO].img_ptr, &(map->textures[NO].bpp), &(map->textures[NO].line_len), &(map->textures[NO].endian));
    if(!map->textures[NO].addr)
        return 0;
    map->textures[SO].addr = mlx_get_data_addr(map->textures[SO].img_ptr, &(map->textures[SO].bpp), &(map->textures[SO].line_len), &(map->textures[SO].endian));
    if(!map->textures[SO].addr)
        return 0;
    map->textures[EA].addr = mlx_get_data_addr(map->textures[EA].img_ptr, &(map->textures[EA].bpp), &(map->textures[EA].line_len), &(map->textures[EA].endian));
    if(!map->textures[EA].addr)
        return 0;
    map->textures[WE].addr = mlx_get_data_addr(map->textures[WE].img_ptr, &(map->textures[WE].bpp), &(map->textures[WE].line_len), &(map->textures[WE].endian));
    if(!map->textures[WE].addr)
        return 0;
    return 1;

}