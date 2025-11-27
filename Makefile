Srcs = srcs/ray_casting/ray_init.c srcs/gnl/get_next_line.c srcs/gnl/get_next_line_utils.c main.c srcs/gnl/maprearding.c srcs/pixels/pixel_drawing.c srcs/keyhooks/key_hooks.c srcs/pixels/player_update.c 

SRCS_CST = srcs/ray_casting/horizontal.c srcs/ray_casting/vertical.c srcs/ray_casting/wall_distance.c

Flags = -lmlx -lXext -lX11 -lm

Mlx_Path = -L/home/aijadid/Desktop/minilibx-linux

Header = includes/get_next_line.h includes/cub3d.h

Name = cube 

all: $(Name)

$(Name): $(Header) $(Srcs) $(SRCS_CST)
	cc -g $(Srcs) $(SRCS_CST) $(Mlx_Path) $(Flags) -o $(Name)

clean:
	rm -rf $(Name)

re: clean all