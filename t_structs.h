/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_structs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:15:29 by scambier          #+#    #+#             */
/*   Updated: 2024/01/28 16:52:26 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_STRUCTS_H
# define T_STRUCTS_H

# include "project.h"
# include "maps.h"

typedef struct s_mlx {
	void	*mlx;
	void	*window;
	int		screen_width;
	int		screen_height;
}	t_mlx;

typedef struct s_all {
	t_mlx		mlx;
	t_map		*map;
	t_camera	*cam;
}	t_all;

#endif