/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:35:59 by scambier          #+#    #+#             */
/*   Updated: 2024/01/26 19:42:26 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "image.h"
#include "libft.h"

static void	put_line_vertical(t_image *img, t_ivec2 *v0, t_ivec2 *v1, int color)
{
	float	a;
	float	b;
	int		k;

	a = (float)(v1->x - v0->x) / (float)(v1->y - v0->y);
	b = -a * (float)v0->y + (float)v0->x;
	k = ft_min(v0->y, v1->y) - 1;
	while (++k <= ft_max(v0->y, v1->y))
		img_put_pixel(img, a * (float)k + b, k, color);
}

static void	put_line_horizontal(t_image *img, t_ivec2 *v0, t_ivec2 *v1, int color)
{
	float	a;
	float	b;
	int		k;

	a = (float)(v1->y - v0->y) / (float)(v1->x - v0->x);
	b = -a * (float)v0->x + (float) v0->y;
	k = ft_min(v0->x, v1->x) - 1;
	while (++k <= ft_max(v0->x, v1->x))
	{
		img_put_pixel(img, k, a * (float)k + b, color);
	}
}

void	put_line(t_image *img, t_ivec2 *v0, t_ivec2 *v1, int color)
{
	if (ft_abs(v1->x - v0->x) > ft_abs(v1->y - v0->y))
		put_line_horizontal(img, v0, v1, color);
	else
		put_line_vertical(img, v0, v1, color);
}
