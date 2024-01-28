/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:12:15 by scambier          #+#    #+#             */
/*   Updated: 2024/01/28 17:29:33 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>

#include "mlx.h"
#include "t_structs.h"
#include "libft.h"
#include "maps.h"

#define M_PI	3.141592653
#define M_PI_4	0.785398163
#define M_PI_16	0.196349541

void	key_hook_clamped(int keycode, t_all *all)
{
	if (keycode == XK_Up)
		all->cam->xr = ft_fclamp(-M_PI_4, all->cam->xr + 0.05f, M_PI_4);
	else if (keycode == XK_Down)
		all->cam->xr = ft_fclamp(-M_PI_4, all->cam->xr - 0.05f, M_PI_4);
	else if (keycode == XK_KP_Add)
		all->cam->scale = ft_clamp(1, all->cam->scale + 1, 32);
	else if (keycode == XK_KP_Subtract)
		all->cam->scale = ft_clamp(1, all->cam->scale - 1, 32);
	else if (keycode == XK_KP_Multiply)
		all->cam->zoom = ft_fclamp(0.5, all->cam->zoom * 1.1, 2.0f);
	else if (keycode == XK_KP_Divide)
		all->cam->zoom = ft_fclamp(0.5, all->cam->zoom / 1.1, 2.0f);
}

void	key_hook_unclamped(int keycode, t_all *all)
{
	if (keycode == XK_Escape)
		mlx_loop_end(all->mlx.mlx);
	else if (keycode == XK_Right)
		all->cam->yr += M_PI_16;
	else if (keycode == XK_Left)
		all->cam->yr -= M_PI_16;
	else if (keycode == 'z')
		all->cam->pos.y += all->cam->scale;
	else if (keycode == 's')
		all->cam->pos.y -= all->cam->scale;
	else if (keycode == 'q')
		all->cam->pos.x += all->cam->scale;
	else if (keycode == 'd')
		all->cam->pos.x -= all->cam->scale;
	else if (keycode == 'i' || keycode == 'o')
		all->cam->proj_type = keycode;
}

int	key_hook(int keycode, t_all *all)
{
	key_hook_clamped(keycode, all);
	key_hook_unclamped(keycode, all);
	draw_map(all);
}

int	close_hook(t_all *all)
{
	mlx_loop_end(all->mlx.mlx);
	return (0);
}

int	expose_hook(t_all *all)
{
	draw_map(all);
}
