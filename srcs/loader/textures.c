/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:03:32 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 15:14:33 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void			ft_read_pixels(int fd, t_texture *result)
{
	read(fd, result->pixels, (result->width * result->height * 4));
}

static t_texture	*ft_verify(int fd, t_texture *result, Uint32 *pixels)
{
	if (fd < 0 || !result || !pixels)
	{
		close(fd);
		free(pixels);
		free(result);
		return (NULL);
	}
	else
		return (result);
}

t_texture			*ft_load_texture(char *filename)
{
	int				fd;
	t_texture		*result;
	Uint32			*pixels;

	pixels = NULL;
	result = NULL;
	fd = open(filename, O_RDONLY);
	if (fd > 0 && (result = malloc(sizeof(t_texture))))
	{
		read(fd, &(result->width), 4);
		read(fd, &(result->height), 4);
		pixels = malloc(sizeof(Uint32) * result->width * result->height);
	}
	else if (!ft_verify(fd, result, pixels))
	{
		ft_putstr("DOOM-NUKEM: cannot read texture : ");
	   ft_putendl(filename);
		return (NULL);
	}
	result->pixels = pixels;
	ft_read_pixels(fd, result);
	close(fd);
	return (result);
}
