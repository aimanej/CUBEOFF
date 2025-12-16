#include "../../includes/cub3d.h"
// #include <stdlib.h>


void ft_free_select(void *ptr)
{
    t_garbage **main_dump = dump_ptr();
    t_garbage *dump = *main_dump;
    t_garbage *tmp = NULL;
    t_mlx *mlx = (*main_dump)->ptr;

    if (!dump || !ptr)
        return;
    while (dump->next && dump->next->ptr && dump->next->ptr != ptr)
    {
        dump = dump->next;
    }
    if (!dump->next)
        return;

    tmp = dump->next;
    dump->next = tmp->next;
    if (tmp->img_t)
        mlx_destroy_image(mlx->mlx, tmp->ptr);
    free(tmp);
}

void ft_free_all()
{
    t_garbage **dump_re = dump_ptr();
    t_garbage *dump = *dump_re;
    t_garbage *tmp = NULL;
    t_mlx *mlx = dump->ptr;

    dump = dump->next;
    while (dump)
    {
        tmp = dump->next;
        if (dump->img_t)
            mlx_destroy_image(mlx->mlx, dump->ptr);
        else
            free(dump->ptr);
        free(dump);
        dump = tmp;
    }
    mlx_destroy_window(mlx->mlx, mlx->win);
    mlx_destroy_display(mlx->mlx);
    free(mlx->mlx);
    free((*dump_re));
    *dump_re = NULL;
    exit(0);
}

void *ft_malloc(size_t size)
{
    t_garbage **dump = dump_ptr();
    void *ptr = NULL;

    ptr = malloc(size);
    if (!ptr)
        return NULL;
    t_garbage *new = ft_new_ptr(ptr, 0);
    if (!new)
    {
        free(ptr);
        return NULL;
    }
    ft_add_last_ptr(dump, new);
    return ptr;
}

void destroy_images(t_mlx *mlx)
{
    int t = 0;
    t_map *map = &(mlx->map);
    while(t <= 3)
    {
        mlx_destroy_image(mlx->mlx, map->textures[t].img_ptr);
        t++;
    }
    mlx_destroy_image(mlx->mlx, map->img.img_ptr);
}
