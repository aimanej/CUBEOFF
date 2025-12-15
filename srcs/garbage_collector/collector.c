#include "../../includes/cub3d.h"
// #include <stdlib.h>

t_garbage **dump_ptr()
{
    static t_garbage *alloced;

    return &alloced;
}
int dump_size(t_garbage *dump)
{
    int t = 0;
    if (!dump)
        return 0;
    while (dump)
    {
        dump = dump->next;
        t++;
    }
    return t;
}

t_garbage *last_garbage(t_garbage *dump)
{
    if (!dump)
        return NULL;
    while (dump->next)
    {
        dump = dump->next;
    }
    return dump;
}

void ft_add_last_ptr(t_garbage **dump, t_garbage *new)
{
    t_garbage *last;

    if (!new)
        return;
    if (!*dump)
    {
        *dump = new;
        new->next = NULL;
        return;
    }
    last = last_garbage(*dump);
    last->next = new;
    new->next = NULL;
}

t_garbage *ft_new_ptr(void *ptr, int type)
{
    t_garbage *new;

    new = malloc(sizeof(t_garbage));
    if (!new)
        return NULL;
    new->ptr = ptr;
    new->img_t = type;
    new->next = NULL;
    return new;
}

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
    printf("mlx in garbage c address : %p\n", mlx);
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