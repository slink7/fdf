/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:12:06 by scambier          #+#    #+#             */
/*   Updated: 2024/01/25 17:09:28 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

#include "libft.h"
#include "maps.h"

t_list	*get_list_from_path(char *file_path)
{
	t_list	*lines;
	char	*temp_line;
	int		fd;

	lines = 0;
	fd = open(file_path, O_RDONLY);
	temp_line = get_next_line(fd);
	while (temp_line)
	{
		ft_lstadd_back(&lines, ft_lstnew(temp_line));
		temp_line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

void	get_tile(t_tile *out, char *str)
{
	out->height = ft_atoi(str);
}

void	get_tiles(int *width, t_tile **out, char *str)
{
	char	**temp;
	int		k;

	temp = ft_split(str, ' ');
	*width = ft_strarrlen(temp);
	*out = malloc(*width * sizeof(t_tile));
	k = -1;
	while (++k < *width)
		get_tile(*out + k, temp[k]);
	ft_strarrfree(temp);
}

t_map	*get_map_from_list(t_list *lst)
{
	t_map	*map;
	int		k;

	map = malloc(sizeof(t_map));
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

void	print_map(t_map *map)
{
	int	k;
	int	l;

	l = -1;
	while (++l < map->height)
	{
		k = -1;
		while (++k < map->width)
		{
			printf("%d ", map->tiles[l][k].height);
		}
		printf("\n");
	}
}

t_map	*load_map(char *file_path)
{
	t_map	*map;
	int		fd;
	t_list	*lines;

	lines = get_list_from_path(file_path);
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
