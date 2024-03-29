/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:30:28 by scambier          #+#    #+#             */
/*   Updated: 2024/01/28 17:56:03 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H

# include "project.h"

typedef struct s_tile {
	int	height;
	int	color;
}	t_tile;

typedef struct s_map {
	int		width;
	int		height;
	t_tile	**tiles;
}	t_map;

typedef struct s_all	t_all;

t_map	*load_map(char *file_path);
void	free_map(t_map **map);
void	draw_map(t_all *all);

#endif