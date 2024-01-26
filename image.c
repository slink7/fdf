/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:50:34 by scambier          #+#    #+#             */
/*   Updated: 2024/01/26 19:40:23 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "image.h"

static void	img_init(t_image *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

t_image	*img_new(void *mlx, int width, int height)
{
	t_image	*out;

	out = malloc(sizeof(t_image));
	if (!out)
		return (0);
	out->img = mlx_new_image(mlx, width, height);
	img_init(out);
	out->width = width;
	out->height = height;
	return (out);
}

void	img_free(void *mlx, t_image **img)
{
	mlx_destroy_image(mlx, (*img)->img);
	free(*img);
	*img = 0;
}

void	img_put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > img->width || y > img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
