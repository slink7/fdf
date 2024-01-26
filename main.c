/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:00:08 by scambier          #+#    #+#             */
/*   Updated: 2024/01/26 15:56:20 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//62863595 72829435

#include <stdlib.h>
#include <math.h>

#include <stdio.h>

#include "mlx.h"
#include "maps.h"
#include "project.h"
#include "libft.h"

#define M_PI	3.14159265358979323846

#define LEFT 65361
#define UP 65362
#define RIGHT 65363
#define DOWN 65364

typedef struct s_mlx {
	void	*mlx;
	void	*window;
}	t_mlx;

typedef struct s_all {
	t_mlx		mlx;
	t_map		*map;
	t_camera	cam;
}	t_all;

void	draw_line(t_mlx *mlx, t_ivec2 *v0, t_ivec2 *v1, int color)
{
	int		dx;
	int		dy;
	float	a;
	float	b;
	int		k;

	dx = v1->x - v0->x;
	dy = v1->y - v0->y;
	if (ft_abs(dx) > ft_abs(dy))
	{
		a = (float) dy / (float) dx;
		b = -a * (float) v0->x + (float) v0->y;
		k = ft_min(v0->x, v1->x) - 1;
		while (++k <= ft_max(v0->x, v1->x))
		{
			mlx_pixel_put(mlx->mlx, mlx->window, k, a * (float) k + b, color);
		}
	}
	else
	{
		a = (float) dx / (float) dy;
		b = -a * (float) v0->y + (float) v0->x;
		k = ft_min(v0->y, v1->y) - 1;
		while (++k <= ft_max(v0->y, v1->y))
		{
			mlx_pixel_put(mlx->mlx, mlx->window, a * (float) k + b, k, color);
		}
	}
}

void	set_vec(t_ivec3 *v, int x, int y, int z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

void	offset(t_ivec2 *v, int x, int y)
{
	v->x += x;
	v->y += y;
}

void	draw_map(t_mlx *mlx, t_camera *cam, t_map *map)
{
	int		k;
	int		l;
	t_ivec3	v3;
	t_ivec2	v2;
	t_ivec2	v21;

	l = -1;
	while (++l < map->height)
	{
		k = -1;
		while (++k < map->width)
		{
			set_vec(&v3, k - map->width / 2, map->tiles[l][k].height, l - map->height / 2);
			project(cam, &v3, &v2);
			offset(&v2, 256, 256);
			if (k < map->width - 1)
			{
				set_vec(&v3, k - map->width / 2 + 1, map->tiles[l][k + 1].height, l - map->height / 2);
				project(cam, &v3, &v21);
				offset(&v21, 256, 256);
				draw_line(mlx, &v2, &v21, map->tiles[l][k].color);
			}
			if (l < map->height - 1)
			{
				set_vec(&v3, k - map->width / 2, map->tiles[l + 1][k].height, l - map->height / 2 + 1);
				project(cam, &v3, &v21);
				offset(&v21, 256, 256);
				draw_line(mlx, &v2, &v21, map->tiles[l][k].color);
			}
		}
	}
}

int	key_hook(int keycode, void *param)
{
	t_all	*all;

	all = param;
	if (keycode == 65307)
		mlx_loop_end(all->mlx.mlx);
	else if (keycode == RIGHT)
		all->cam.yr += M_PI * 0.1f;
	else if (keycode == LEFT)
		all->cam.yr -= M_PI * 0.1f;
	else if (keycode == UP)
		all->cam.xr = ft_fclamp(0.0f, all->cam.xr + 0.05f, 1.0f);
	else if (keycode == DOWN)
		all->cam.xr = ft_fclamp(0.0f, all->cam.xr - 0.05f, 1.0f);
	else if (keycode == 'o')
		all->cam.scale = ft_clamp(0, all->cam.scale + 1, 16);
	else if (keycode == 'p')
		all->cam.scale = ft_clamp(0, all->cam.scale - 1, 16);
	else if (keycode == 'k')
		all->cam.zoom = ft_fclamp(0.0, all->cam.zoom * 1.01, 1.0f);
	else if (keycode == 'l')
		all->cam.zoom = ft_fclamp(0.0, all->cam.zoom / 1.01, 1.0f);
	mlx_clear_window(all->mlx.mlx, all->mlx.window);
	draw_map(&all->mlx, &all->cam, all->map);
	return (1);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc != 2)
		return (0);
	all.mlx.mlx = mlx_init();
	all.mlx.window = mlx_new_window(all.mlx.mlx, 512, 512, "Fenetre de zinzin");
	mlx_key_hook(all.mlx.window, key_hook, &all);
	all.map = load_map(argv[1]);
	all.cam.scale = 8;
	all.cam.yr = 0.0f;
	all.cam.xr = 0.5f;
	all.cam.zoom = 1.0f;
	draw_map(&all.mlx, &all.cam, all.map);
	mlx_loop(all.mlx.mlx);
	free_map(&all.map);
	mlx_destroy_window(all.mlx.mlx, all.mlx.window);
	mlx_destroy_display(all.mlx.mlx);
	free(all.mlx.mlx);
}
