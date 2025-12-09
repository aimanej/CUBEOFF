#include "../includes/cub.h"

int is_surrounded_by_walls(t_map *map)
{
    int i;
    int j;


    i = 1;
    j = 0;
    while(map->map[0][j])
    {
        if(map->map[0][j] != '1' && !is_space(map->map[0][j]))
            return 1;
        j++;
    }
    j=0;
    while(map->map[map->size - 1][j])
    {
        if(map->map[map->size - 1][j] != '1'&& !is_space(map->map[map->size - 1][j]))
            return 1;
        j++;
    }
    while (map->map[i])
    {
        if((map->map[i][0] != '1' && !is_space(map->map[i][0])) || (map->map[i][ft_strlen(map->map[i]) - 1] != '1' && !is_space(map->map[i][ft_strlen(map->map[i]) - 1])))
            return 1;
        i++;
    }
    return 0;
}


char	*ft_strdup1(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

void allocate_map(t_map *map, char *filename)
{
    char *line;
    int fd;
    int i;

    i = 0;
    fd = open(filename, O_RDONLY);
    if(fd == -1)
    {
        printf("ERROR/open");
        exit(1);
    }
    printf("map size : %d \n", map->size);
    map->map = ft_malloc((map->size + 1) * sizeof(char *));
    line = get_next_line(fd);
    while(line)
    {
        if(is_map(line))
        {
            map->map[i] = ft_strdup1(line);
            i++;
        }
        free(line);
        line = get_next_line(fd);
    }
    if(!line)
        free(line);
    close(fd);
    map->map[i] = 0;
}

void player_angle_set(t_map *map, char c)
{
    map->player.player_dir = c;
    if(c == 'N')
        map->player.view_angle = 270 * (PI / 180);
    else if(c == 'S')
        map->player.view_angle = 90 * (PI / 180);
    else if(c == 'E')
        map->player.view_angle = 0 * (PI / 180);
    else if(c == 'W')
        map->player.view_angle = 180 * (PI / 180);
    player_direction(&(map->player));
}

int map_elements(t_map *map)
{
    int i;
    int j;

    i = 0;
    while(map->map[i])
    {
        j = 0;
        while(map->map[i][j])
        {
            if(ft_strchr("10NSEW",map->map[i][j]) || is_space(map->map[i][j]))
            {
                if(ft_strchr("NSEW", map->map[i][j]))
                {
                    player_angle_set(map , map->map[i][j]);
                    map->player.center_pos.row = i * TILE_SIZE + (TILE_SIZE / 2);
                    map->player.center_pos.col = j * TILE_SIZE + (TILE_SIZE / 2);
                }   
            }
            else if (map->map[i][j])
                return 1;
            j++;

        }
        i++;
    }
    return 0;
}

int valid_spaces(t_map *map)
{
    int i;
    int w;
    int j;

    i = 0;
    w = 0;
    while(map->map[i])
    {
        if((int)ft_strlen(map->map[i]) > w)
            w = ft_strlen(map->map[i]);
        i++;
    }
    i = 0;

    while(map->map[i])
    {
        j =0;
        while(map->map[i][j])
        {
            if(map->map[i][j] == '0')
            {
                if(!parse_spaces(map->map,i,j,map->size, map->player.player_dir))
                {
                    printf("%c ,%d, %d\n",map->map[i][j], i, j);
                    return 1;
                }
            }
            j++;
        }
        i++;
    }
    return 0;
}                                               

int parse_spaces(char **map, int i,int j, int count, char d)
{
    if(i < 0 || i >= count)
        return 0;
    if(j < 0 || j>= (int)ft_strlen(map[i]))
        return 0;

    if(map[i][j] == '1' ||map[i][j] == 'o'|| map[i][j] == d)
        return 1;
    
    
    if(map[i][j] !='0')
        return 0;
     map[i][j] = 'o';
    if(!parse_spaces(map,i+1, j,count,d))
        return 0;
    if(!parse_spaces(map,i, j-1,count, d))
        return 0;
    if(!parse_spaces(map,i-1, j,count, d))
        return 0;
    if(!parse_spaces(map,i, j+1,count, d))
        return 0;
    return 1;


}

void parse_map(t_map *map)
{


    if(map_elements(map))
        error("invalid map elements");
    if(valid_spaces(map))
        error("invalid spaces");
    if(is_surrounded_by_walls(map))
        error("not surrounded by wall");
    
    
}