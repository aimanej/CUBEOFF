#include "../../includes/cub3d.h"

void image_converter(t_mlx *mlx)
{
    t_image *textures = mlx->map.textures;
    textures[NO].img_ptr = mlx_xpm_file_to_image(mlx->mlx, textures[NO].path, &(textures[NO].width), &(textures[NO].height));
    if (!textures[NO].img_ptr)
        return ft_free_all();
    ft_add_last_ptr(dump_ptr(), ft_new_ptr(textures[NO].img_ptr, 1));
    textures[SO].img_ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->map.textures[SO].path, &(textures[SO].width), &(textures[SO].height));
    if (!textures[SO].img_ptr)
        return ft_free_all();
    ft_add_last_ptr(dump_ptr(), ft_new_ptr(textures[SO].img_ptr, 1));
    textures[EA].img_ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->map.textures[EA].path, &(textures[EA].width), &(textures[EA].height));
    if (!textures[EA].img_ptr)
        return ft_free_all();
    ft_add_last_ptr(dump_ptr(), ft_new_ptr(textures[EA].img_ptr, 1));
    textures[WE].img_ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->map.textures[WE].path, &(textures[WE].width), &(textures[WE].height));
    if (!textures[WE].img_ptr)
        return ft_free_all();
    ft_add_last_ptr(dump_ptr(), ft_new_ptr(textures[WE].img_ptr, 1));
}

void image_address(t_mlx *mlx)
{
    t_image *textures = mlx->map.textures;

    textures[NO].addr = mlx_get_data_addr(textures[NO].img_ptr, &(textures[NO].bpp), &(textures[NO].line_len), &(textures[NO].endian));
    if (!textures[NO].addr)
        return ft_free_all();
    textures[SO].addr = mlx_get_data_addr(textures[SO].img_ptr, &(textures[SO].bpp), &(textures[SO].line_len), &(textures[SO].endian));
    if (!textures[SO].addr)
        return ft_free_all();
    textures[EA].addr = mlx_get_data_addr(textures[EA].img_ptr, &(textures[EA].bpp), &(textures[EA].line_len), &(textures[EA].endian));
    if (!textures[EA].addr)
        return ft_free_all();
    textures[WE].addr = mlx_get_data_addr(textures[WE].img_ptr, &(textures[WE].bpp), &(textures[WE].line_len), &(textures[WE].endian));
    if (!textures[WE].addr)
        return ft_free_all();
}

int texture_init(t_mlx *mlx)
{
    image_converter(mlx);
    image_address(mlx);
}
