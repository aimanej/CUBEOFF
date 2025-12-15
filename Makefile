Srcs = srcs/garbage_collector/collector.c main.c srcs/ray_casting/ray_init.c  srcs/pixels/pixel_drawing.c srcs/hooks_updates/key_hooks.c srcs/hooks_updates/player_update.c 
NEWSRC = parsing/utils.c parsing/gnl/get_next_line_utils.c parsing/gnl/get_next_line.c parsing/ft_strncmp.c parsing/parsing.c parsing/ft_isdigit.c parsing/ft_split.c parsing/ft_atoi.c parsing/map_parsing.c
SRCS_CST = srcs/initializers/texture_init.c srcs/ray_casting/textures.c srcs/pixels/array_drawing.c srcs/hooks_updates/angle_norm.c srcs/hooks_updates/gameloop.c srcs/initializers/map_init.c srcs/initializers/ray_init.c srcs/hooks_updates/player_pos.c srcs/ray_casting/horizontal.c srcs/ray_casting/vertical.c



Flags = -lmlx -lXext -lX11 -lm

Mlx_Path = -L /home/aimane-jadid/Desktop/studies/minilibx-linux/

Headers = includes/get_next_line.h includes/cub3d.h includes/cub.h

Name = cube 

all: $(Name)

$(Name): $(Header) $(Srcs) $(SRCS_CST) $(NEWSRC)
	cc -g $(Srcs) $(SRCS_CST) $(NEWSRC) $(Mlx_Path) $(Flags) -o $(Name)

clean:
	rm -rf $(Name)

re: clean all