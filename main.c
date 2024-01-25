/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:00:08 by scambier          #+#    #+#             */
/*   Updated: 2024/01/25 17:40:44 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include <stdio.h>

#include "mlx.h"
#include "maps.h"
#include "project.h"
#include "libft.h"

# define M_PI		3.14159265358979323846

#define LEFT 65361
#define UP 65362
#define RIGHT 65363
#define DOWN 65364

typedef struct s_mlx {
	void	*mlx;
	void	*window;
}	t_mlx;

typedef struct {
	t_mlx		mlx;
	t_map		*map;
	t_camera	cam;
}	t_all;



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

int	key_hook(int keycode, void *param)
{
	t_all *all;

	all = param;
	if (keycode == 65307)
		mlx_loop_end(all->mlx.mlx);
	else if (keycode == RIGHT)
		all->cam.yr += M_PI * 0.1f;
	else if (keycode == LEFT)
		all->cam.yr -= M_PI * 0.1f;
	else if (keycode == UP)
		all->cam.xr += 0.05f;
	else if (keycode == DOWN)
		all->cam.xr -= 0.05f;
	else if (keycode == 'o')
		all->cam.scale += 1;
	else if (keycode == 'p')
		all->cam.scale -= 1;
	else if (keycode == 'k')
		all->cam.zoom *= 0.1f;
	else if (keycode == 'l')
		all->cam.zoom /= 0.1f; 
	mlx_clear_window(all->mlx.mlx, all->mlx.window);
	draw_map(&all->mlx, &all->cam, all->map);
	return (1);
}

int	main(int argc, char **argv)
{
	t_all all;

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
