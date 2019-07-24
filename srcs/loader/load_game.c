/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:52:26 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 15:14:19 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

/*
 * **	This function will read the header of the map, containing the sector
 * **		number, texture number, sky texture, player start x and y position
 * */

int			ft_read_header(t_game *map, int fd)
{
	char	*line;
	char	**table;

	if (get_next_line(fd, &line) > 0)
	{
		table = ft_strsplit(line, ' ');
		if (ft_tabsize(table) != 5)
			return (0);
		map->sector_count = ft_atoi(table[0]);
		map->texture_count = ft_atoi(table[1]);
		map->sky_texture = ft_atoi(table[2]);
		ft_tabfree(table);
		free(line);
	}
	else
		return (0);
	return (1);
}

t_texture	*ft_load_texture(char *filename)
{
	t_texture	*texture;
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	texture = ft_memalloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	read(fd, &texture->width, 4);
	read(fd, &texture->height, 4);
	texture->pixels = malloc(sizeof(Uint32) * texture->width * texture->height);
	read(fd, texture->pixels, texture->width * texture->height * 4);
	return (texture);
}
/*
 * **	this function will load the textures given in the map file
 * */

int			ft_store_textures(t_game *map, int fd)
{
	Uint32			i;
	t_texture	*result;
	char		*line;

	i = 0;
	map->textures = malloc(sizeof(t_texture) * map->texture_count);
	map->renderer.textures = map->textures;
	map->renderer.texture_count = map->texture_count;
	while (i < map->texture_count && get_next_line(fd, &line) > 0)
	{
		result = ft_load_texture(line);
		if (!result)
		{
			free(map->textures);
			return (0);
		}
		(map->textures)[i] = *result;
		free(line);
		i++;
	}
	return (1);
}

/*
 * **	This function will take the filename and an address to an int
 * **		that will be asigned the number of sectors loaded
 * **		the return value is an array of t_sector of length sector_count
 * **	If file cannot be opened or an error occures, the function returns NULL
 * */

t_sector	*ft_load_sectors(const char *file_name, t_game	*m)
{
	int			fd;
	t_sector	*sect;

	fd = open(file_name, O_RDONLY);
	ft_putnbr(fd);
	if (fd < 0 || fd > 4096 || !ft_read_header(m, fd))
		return (NULL);
	if (!(sect = (t_sector *)ft_memalloc(sizeof(t_sector) * m->sector_count)))
		return (NULL);
	if (!ft_store_textures(m, fd) || !ft_load_sector_data(sect, fd))
	{
		free(sect);
		return (NULL);
	}
	ft_putendl("All Sectors were succesfully loaded");
	close(fd);
	return (sect);
}

