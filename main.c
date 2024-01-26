/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:00:08 by scambier          #+#    #+#             */
/*   Updated: 2024/01/26 19:43:49 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//62863595 72829435

#include <stdlib.h>
#include <math.h>

#include <stdio.h>

#include "mlx.h"
#include "maps.h"
#include "project.h"
#include "image.h"
#include "put_line.h"
#include "libft.h"

#define M_PI	3.14159265358979323846

#define LEFT 65361
#define UP 65362
#define RIGHT 65363
#define DOWN 65364

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512

typedef struct s_mlx {
	void	*mlx;
	void	*window;
}	t_mlx;

typedef struct s_all {
	t_mlx		mlx;
	t_map		*map;
	t_camera	*cam;
}	t_all;

void	draw_map(t_mlx *mlx, t_camera *cam, t_map *map)
{
	int		k;
	int		l;
	t_ivec3	v3;
	t_ivec2	v2;
	t_ivec2	v21;
	t_image	*bb;

	bb = img_new(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	l = -1;
	while (++l < map->height)
	{
		k = -1;
		while (++k < map->width)
		{
			set_vec(&v3, k - map->width / 2, map->tiles[l][k].height, l - map->height / 2);
			project(cam, &v3, &v2);
			offset(&v2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
			if (k < map->width - 1)
			{
				set_vec(&v3, k - map->width / 2 + 1, map->tiles[l][k + 1].height, l - map->height / 2);
				project(cam, &v3, &v21);
				offset(&v21, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
				put_line(bb, &v2, &v21, map->tiles[l][k].color);
			}
			if (l < map->height - 1)
			{
				set_vec(&v3, k - map->width / 2, map->tiles[l + 1][k].height, l - map->height / 2 + 1);
				project(cam, &v3, &v21);
				offset(&v21, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
				put_line(bb, &v2, &v21, map->tiles[l][k].color);
			}
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, bb->img, 0, 0);
	img_free(mlx->mlx, &bb);
}

int	key_hook(int keycode, void *param)
{
	t_all	*all;

	all = param;
	if (keycode == 65307)
		mlx_loop_end(all->mlx.mlx);
	else if (keycode == RIGHT)
		all->cam->yr += M_PI * 0.1f;
	else if (keycode == LEFT)
		all->cam->yr -= M_PI * 0.1f;
	else if (keycode == UP)
		all->cam->xr = ft_fclamp(0.0f, all->cam->xr + 0.05f, 1.0f);
	else if (keycode == DOWN)
		all->cam->xr = ft_fclamp(0.0f, all->cam->xr - 0.05f, 1.0f);
	else if (keycode == 'o')
		all->cam->scale = ft_clamp(1, all->cam->scale + 1, 32);
	else if (keycode == 'p')
		all->cam->scale = ft_clamp(1, all->cam->scale - 1, 32);
	else if (keycode == 'k')
		all->cam->zoom = ft_fclamp(0.5, all->cam->zoom * 1.1, 2.0f);
	else if (keycode == 'l')
		all->cam->zoom = ft_fclamp(0.5, all->cam->zoom / 1.1, 2.0f);
	mlx_clear_window(all->mlx.mlx, all->mlx.window);
	draw_map(&all->mlx, all->cam, all->map);
	return (1);
}

void	init(t_all *all)
{
	all->mlx.mlx = mlx_init();
	all->mlx.window = mlx_new_window(all->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Fenetre de zinzin");
	all->cam = new_cam(8, 0.0f, 0.5f, 1.0f);
}

void	deinit(t_all *all)
{
	mlx_destroy_window(all->mlx.mlx, all->mlx.window);
	mlx_destroy_display(all->mlx.mlx);
	free(all->mlx.mlx);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc != 2)
	{
		ft_putstr_fd("Wrong number of args : ./fdf <map.fdf>\n", 2);
		return (1);
	}
	init(&all);
	mlx_key_hook(all.mlx.window, key_hook, &all);
	all.map = load_map(argv[1]);
	draw_map(&all.mlx, all.cam, all.map);
	mlx_loop(all.mlx.mlx);
	free_map(&all.map);
	deinit(&all);
}
