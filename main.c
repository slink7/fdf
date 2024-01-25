/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:00:08 by scambier          #+#    #+#             */
/*   Updated: 2024/01/25 16:38:02 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include <stdio.h>

#include "mlx.h"
#include "maps.h"
#include "project.h"
#include "libft.h"

typedef struct s_mlx {
	void	*mlx;
	void	*window;
}	t_mlx;

int	key_hook(int keycode, void *param)
{
	if (keycode == 65307)
		mlx_loop_end(((t_mlx *)param)->mlx);
	return (1);
}

/*
void	CR_draw_line(t_window *w, t_vec2i *p0, t_vec2i *p1, float v)
{
	int dx = p1->x - p0->x;
	int dy = p1->y - p0->y;
	if (abs(dx) > abs(dy)) {
		float a = (float) dy / (float) dx;
		float b = - a * (float) p0->x + (float) p0->y;
		for (int k = min(p0->x, p1->x); k <= max(p0->x, p1->x); k++)
			CR_draw(w, &(t_vec2i) {k, (int) round(a * (float) k + b)}, v);
	} else {
		float a = (float) dx / (float) dy;
		float b = - a * (float) p0->y + (float) p0->x;
		for (int k = min(p0->y, p1->y); k <= max(p0->y, p1->y); k++)
			CR_draw(w, &(t_vec2i) {(int) round(a * (float) k + b), k}, v);
	}
}
*/

void	draw_line(t_mlx *mlx, t_ivec2 *v0, t_ivec2 *v1)
{
	int		dx;
	int		dy;
	float	a;
	float	b;
	int 	k;
	int		l;

	dx = v1->x - v0->x;
	dy = v1->y - v0->y;
	if (ft_abs(dx) > ft_abs(dy))
	{
		a = (float) dy / (float) dx;
		b = -a * (float) v0->x + (float) v0->y;
		k = ft_min(v0->x, v1->x) - 1;
		while (++k <= ft_max(v0->x, v1->x))
		{
			l = a * (float) k + b;
			mlx_pixel_put(mlx->mlx, mlx->window, k, l, 0x00FF00);
		}
	}
	else
	{
		a = (float) dx / (float) dy;
		b = -a * (float) v0->y + (float) v0->x;
		k = ft_min(v0->y, v1->y) - 1;
		while (++k <= ft_max(v0->y, v1->y))
		{
			l = a * (float) k + b;
			mlx_pixel_put(mlx->mlx, mlx->window, l, k, 0x00FF00);
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
	int	k;
	int	l;
	t_ivec3 v3;
	t_ivec2 v2;
	t_ivec2 v21;

	l = -1;
	while (++l < map->height)
	{
		k = -1;
		while (++k < map->width)
		{
			set_vec(&v3, k - map->height / 2, map->tiles[l][k].height, l - map->width / 2);
			project(cam, &v3, &v2);
			offset(&v2, 256, 256);
			if (k < map->width - 1)
			{
				set_vec(&v3, k - map->height / 2 + 1, map->tiles[l][k + 1].height, l - map->width / 2);
				project(cam, &v3, &v21);
				offset(&v21, 256, 256);
				draw_line(mlx, &v2, &v21);
			}
			if (l < map->height - 1)
			{
				set_vec(&v3, k - map->height / 2, map->tiles[l + 1][k].height, l - map->width / 2 + 1);
				project(cam, &v3, &v21);
				offset(&v21, 256, 256);
				draw_line(mlx, &v2, &v21);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;
	t_map		*map;
	t_camera	cam;

	if (argc != 2)
		return (0);
	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, 512, 512, "Fenetre de zinzin");
	mlx_key_hook(mlx.window, key_hook, &mlx);
	map = load_map(argv[1]);
	cam.scale = 8;
	cam.yr = 45.0f;
	draw_map(&mlx, &cam, map);
	mlx_loop(mlx.mlx);
	free_map(&map);
	mlx_destroy_window(mlx.mlx, mlx.window);
	mlx_destroy_display(mlx.mlx);
	free(mlx.mlx);
}
