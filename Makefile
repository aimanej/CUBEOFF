Srcs = get_next_line.c get_next_line_utils.c main.c maprearding.c pixel_drawing.c key_hooks.c

Flags = -lmlx -lXext -lX11 -lm

Mlx_Path = -L/home/aimane-jadid/Desktop/minilibx-linux

Header = get_next_line.h cub3d.h

Name = cube 

all: $(Name)

$(Name): $(Header) $(Srcs)
	cc $(Srcs) $(Mlx_Path) $(Flags) -o $(Name)

clean:
	rm -rf $(Name)

re: clean all