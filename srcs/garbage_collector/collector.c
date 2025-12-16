#include "../../includes/cub3d.h"

// #include <stdlib.h>

void	ft_free_select(void *ptr)
{
	t_garbage	**main_dump;
	t_garbage	*dump;
	t_garbage	*tmp;
	t_mlx		*mlx;

	main_dump = dump_ptr();
	dump = *main_dump;
	tmp = NULL;
	mlx = (*main_dump)->ptr;
	if (!dump || !ptr)
		return ;
	while (dump->next && dump->next->ptr && dump->next->ptr != ptr)
	{
		dump = dump->next;
	}
	if (!dump->next)
		return ;
	tmp = dump->next;
	dump->next = tmp->next;
	if (tmp->img_t)
		mlx_destroy_image(mlx->mlx, tmp->ptr);
	free(tmp);
}

static void	disp_win_destroy(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}

void	ft_free_all(void)
{
	t_garbage	**dump_re;
	t_garbage	*dump;
	t_garbage	*tmp;
	t_mlx		*mlx;

	dump_re = dump_ptr();
	dump = *dump_re;
	tmp = NULL;
	mlx = dump->ptr;
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
	disp_win_destroy(mlx);
	free((*dump_re));
	*dump_re = NULL;
	exit(0);
}

void	*ft_malloc(size_t size)
{
	t_garbage	**dump;
	void		*ptr;
	t_garbage	*new;

	dump = dump_ptr();
	ptr = NULL;
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new = ft_new_ptr(ptr, 0);
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	ft_add_last_ptr(dump, new);
	return (ptr);
}

void	destroy_images(t_mlx *mlx)
{
	int		t;
	t_map	*map;

	t = 0;
	map = &(mlx->map);
	while (t <= 3)
	{
		mlx_destroy_image(mlx->mlx, map->textures[t].img_ptr);
		t++;
	}
	mlx_destroy_image(mlx->mlx, map->img.img_ptr);
}
