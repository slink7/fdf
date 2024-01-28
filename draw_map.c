/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:27:08 by scambier          #+#    #+#             */
/*   Updated: 2024/01/28 17:53:35 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_structs.h"
#include "put_line.h"
#include "project.h"
#include "image.h"
#include "maps.h"
#include "mlx.h"

void	draw_tile(t_all *all, t_image *buffer, t_ivec2 p)
{
	t_ivec3	v3;
	t_ivec2	v2;
	t_ivec2	v21;
	t_ivec2	h;

	h = (t_ivec2){all->map->width / 2, all->map->height / 2};
	sv(&v3, p.x - h.x, all->map->tiles[p.y][p.x].height, p.y - h.y);
	project(all->cam, &v3, &v2);
	offset(&v2, all->mlx.screen_width / 2, all->mlx.screen_height / 2);
	offset(&v2, all->cam->pos.x, all->cam->pos.y);
	if (p.x < all->map->width - 1)
	{
		sv(&v3, p.x - h.x + 1, all->map->tiles[p.y][p.x + 1].height, p.y - h.y);
		project(all->cam, &v3, &v21);
		offset(&v21, all->mlx.screen_width / 2, all->mlx.screen_height / 2);
		offset(&v21, all->cam->pos.x, all->cam->pos.y);
		put_line(buffer, &v2, &v21, all->map->tiles[p.y][p.x].color);
	}
	if (p.y >= all->map->height - 1)
		return ;
	sv(&v3, p.x - h.x, all->map->tiles[p.y + 1][p.x].height, p.y - h.y + 1);
	project(all->cam, &v3, &v21);
	offset(&v21, all->mlx.screen_width / 2, all->mlx.screen_height / 2);
	offset(&v21, all->cam->pos.x, all->cam->pos.y);
	put_line(buffer, &v2, &v21, all->map->tiles[p.y][p.x].color);
}

void	draw_map(t_all *all)
{
	int		k;
	int		l;
	t_image	*bb;

	bb = img_new(all->mlx.mlx, all->mlx.screen_width, all->mlx.screen_height);
	l = -1;
	while (++l < all->map->height)
	{
		k = -1;
		while (++k < all->map->width)
			draw_tile(all, bb, (t_ivec2){k, l});
	}
	mlx_clear_window(all->mlx.mlx, all->mlx.window);
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.window, bb->img, 0, 0);
	img_free(all->mlx.mlx, &bb);
}
