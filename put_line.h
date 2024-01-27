/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:08:47 by scambier          #+#    #+#             */
/*   Updated: 2024/01/27 19:31:19 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_LINE_H
# define PUT_LINE_H

# include "image.h" 
# include "vec.h" 

void	put_line(t_image *img, t_ivec2 *v0, t_ivec2 *v1, int color);

#endif