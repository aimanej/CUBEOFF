#include "../../includes/cub3d.h"

char	**parsing(t_map *map_s, char *av)
{
	char	**arr;
	int		t;
	int		p;
	int		fd;

	p = 0;
	t = 0;
	t = map_height(map_s, av);
	if (t == -1)
		return (NULL);
	fd = open(av, O_RDWR, 777);
	if (fd < 2)
		return (NULL);
	arr = malloc(sizeof(char *) * (t + 1));
	if (!arr)
		return (NULL);
	while (t + 1)
	{
		arr[p] = get_next_line(fd);
		t--;
		p++;
	}
	close(fd);
	return (arr);
}

int	map_height(t_map *map_s, char *av)
{
	int		fd;
	char	*str;
	int		t;

	t = 0;
	fd = open(av, O_RDWR, 777);
	if (fd < 2)
		return (-1);
	str = get_next_line(fd);
	if (str == NULL)
		return (-1);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		t++;
	}
	close(fd);
	map_s->size = t;
	return (t);
}

void	fputchar(char c)
{
	write(1, &c, 1);
}

void	lil_nbr(int t)
{
	if (t > 9)
	{
		lil_nbr(t / 10);
	}
	fputchar((t % 10) + 48);
}
