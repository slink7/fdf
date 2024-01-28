/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:00:08 by scambier          #+#    #+#             */
/*   Updated: 2024/01/28 18:10:48 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//62863595 72829435

#include <stdlib.h>
#include <math.h>

#include <stdio.h>

#include <X11/keysym.h>
#include <X11/X.h>

#include "libft.h"
#include "mlx.h"
#include "maps.h"
#include "hooks.h"
#include "project.h"
#include "t_structs.h"

void	init(t_all *all)
{
	all->mlx.screen_width = 1024;
	all->mlx.screen_height = 512;
	all->mlx.mlx = mlx_init();
	all->mlx.window = mlx_new_window(
			all->mlx.mlx,
			all->mlx.screen_width, all->mlx.screen_height,
			"Fenetre de zinzin");
	all->cam = new_cam(8, 0.0f, 0.0f, 1.0f);
}

void	deinit(t_all *all)
{
	free(all->cam);
	mlx_destroy_window(all->mlx.mlx, all->mlx.window);
	mlx_destroy_display(all->mlx.mlx);
	free(all->mlx.mlx);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc != 2)
	{
		ft_printf_fd(2, "Wrong number of args : ./fdf <map.fdf>\n");
		return (1);
	}
	init(&all);
	mlx_hook(all.mlx.window, DestroyNotify, ButtonPressMask, close_hook, &all);
	mlx_hook(all.mlx.window, KeyPress, KeyPressMask, key_hook, &all);
	mlx_hook(all.mlx.window, Expose, ExposureMask, expose_hook, &all);
	all.map = load_map(argv[1]);
	if (!all.map)
	{
		ft_printf_fd(2, "Wrong map name : \"%s\" does not exists\n", argv[1]);
		return (1);
	}
	draw_map(&all);
	mlx_loop(all.mlx.mlx);
	free_map(&all.map);
	deinit(&all);
}
