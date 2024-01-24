/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:00:08 by scambier          #+#    #+#             */
/*   Updated: 2024/01/24 21:18:27 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "mlx.h"
#include "maps.h"

typedef struct s_mlx {
	void	*mlx;
	void	*window;
}	t_mlx;

int	key_hook(int keycode, void *param)
{
	if (keycode == 65307)
		mlx_loop_end(((t_mlx*)param)->mlx);
	return (1);
}

int	main(int argc, char** argv)
{	
	t_mlx	mlx;
	t_map	*map;

	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, 128, 128, "Fenetre de zinzin");
	mlx_key_hook(mlx.window, key_hook, &mlx);
	map = load_map("maps/pyramide.fdf");
	mlx_loop(mlx.mlx);
	free_map(&map);
	mlx_destroy_window(mlx.mlx, mlx.window);
	mlx_destroy_display(mlx.mlx);
	free(mlx.mlx);
}