#include "../../includes/cub3d.h"


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