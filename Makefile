Srcs = srcs/ray_casting/ray_init.c srcs/gnl/get_next_line.c srcs/gnl/get_next_line_utils.c main.c srcs/gnl/maprearding.c srcs/pixels/pixel_drawing.c srcs/hooks_updates/key_hooks.c srcs/hooks_updates/player_update.c 

SRCS_CST = srcs/ray_casting/textures.c srcs/pixels/array_drawing.c srcs/pixels/mini_map.c srcs/hooks_updates/angle_norm.c srcs/hooks_updates/gameloop.c srcs/initializers/map_init.c srcs/initializers/ray_init.c srcs/hooks_updates/player_pos.c srcs/ray_casting/horizontal.c srcs/ray_casting/vertical.c

Flags = -lmlx -lXext -lX11 -lm

Mlx_Path = -L/home/aimane-jadid/Desktop/studies/minilibx-linux

Header = includes/get_next_line.h includes/cub3d.h

Name = cube 

all: $(Name)

$(Name): $(Header) $(Srcs) $(SRCS_CST)
	cc -g $(Srcs) $(SRCS_CST) $(Mlx_Path) $(Flags) -o $(Name)

clean:
	rm -rf $(Name)

re: clean all