/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:12:06 by scambier          #+#    #+#             */
/*   Updated: 2024/01/28 17:57:28 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

#include "libft.h"
#include "maps.h"

#define INT_MAX	0x7FFFFFFF
#define GREY	0x888888
#define WHITE	0xFFFFFF

static t_list	*get_list_from_path(char *file_path)
{
	t_list	*lines;
	char	*temp_line;
	int		fd;

	lines = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 1)
		return (0);
	temp_line = get_next_line(fd);
	while (temp_line)
	{
		ft_lstadd_back(&lines, ft_lstnew(temp_line));
		temp_line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

static void	get_tiles(int *width, t_tile **out, char *str)
{
	char	**temp;
	char	*chr;
	int		k;

	temp = ft_split(str, ' ');
	*width = ft_min(*width, ft_strarrlen(temp));
	*out = malloc(*width * sizeof(t_tile));
	k = -1;
	while (++k < *width)
	{
		(*out + k)->height = ft_atoi(temp[k]);
		chr = ft_strchr(temp[k], ',');
		if (!chr)
			(*out + k)->color = WHITE;
		else
			(*out + k)->color = ft_atoi_base(chr + 3, "0123456789ABCDEF");
	}
	ft_strarrfree(temp);
}

static t_map	*get_map_from_list(t_list *lst)
{
	t_map	*map;
	int		k;

	map = malloc(sizeof(t_map));
	map->width = INT_MAX;
	map->height = ft_lstsize(lst);
	map->tiles = malloc(map->height * sizeof(t_tile *));
	k = -1;
	while (++k < map->height)
	{
		get_tiles(&map->width, map->tiles + k, (char *)lst->content);
		lst = lst->next;
	}
	return (map);
}

t_map	*load_map(char *file_path)
{
	t_map	*map;
	int		fd;
	t_list	*lines;

	lines = get_list_from_path(file_path);
	if (!lines)
		return (0);
	map = get_map_from_list(lines);
	ft_lstclear(&lines, free);
	return (map);
}

void	free_map(t_map **map)
{
	int	k;

	k = -1;
	while (++k < (*map)->height)
		free((*map)->tiles[k]);
	free((*map)->tiles);
	free(*map);
	*map = 0;
}
