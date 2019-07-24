/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:02:09 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 15:16:26 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

/*
**	This function reads the line given and extract portal information
**		then adds a new portal to the sector
*/

static	int			ft_parse_portal(t_sector *sector, char *line, int index)
{
	t_portal	*portal;
	char **table;

	table = ft_strsplit(line, ' ');
	if (ft_tabsize(table) != 6)
	{
		ft_tabfree(table);
		return (0);
	}
	portal = ft_new_portal(
					(t_point){ft_atoi(table[0]), ft_atoi(table[1])},
					(t_point){ft_atoi(table[2]), ft_atoi(table[3])},
					&(sector[ft_atoi(table[4])]), 0);
	portal->wall.texture = ft_atoi(table[5]);
	ft_list_push(&(sector[index].portals), ft_list_newnode(portal));
	return (1);
}

/*
**	This function parses the walls data
*/

static	int			ft_parse_wall(t_sector *sector, char *line, int index)
{
	char	**table;
	int		texture;

	table = ft_strsplit(line, ' ');
	if (ft_tabsize(table) != 6)
	{
		ft_tabfree(table);
		return (0);
	}
	if ((texture = ft_atoi(table[4])) < 0)
		return (0);
	ft_list_push(&(sector[index].walls), ft_list_newnode(ft_new_wall(
					(t_point){ft_atoi(table[0]), ft_atoi(table[1])},
					(t_point){ft_atoi(table[2]), ft_atoi(table[3])},
					texture, ft_atoi(table[5]))));
	return (1);
}

/*
**	This function parses the sector line to get floor and ceiling height
**		number of walls and number of portals
*/

static	int			ft_parse_sector(char *line, t_sector *sector, int index)
{
	char **table;

	table = ft_strsplit(line, ' ');
	if (ft_tabsize(table) != 7)
		return (0);
	sector[index].ceil_height = ft_atoi(table[1]);
	sector[index].floor_height = ft_atoi(table[2]);
	sector[index].ceil_tex = ft_atoi(table[3]);
	sector[index].floor_tex = ft_atoi(table[4]);
	ft_tabfree(table);
	return (1);
}

/*
**	This function actually loads the data from the file to the previously
**		allocated array of sectors
*/

int					ft_load_sector_data(t_sector *result, int fd)
{
	char	*line;
	int		index;
	int		portals;
	int		iserror;

	index = -1;
	portals = 0;
	iserror = 1;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strstr(line, "sector:") && !(portals = 0))
			ft_parse_sector(line, result, ++index);
		else if (ft_strstr(line, "portals:"))
			portals = 1;
		else if (portals == 0)
			iserror &= ft_parse_wall(result, line, index);
		else
			iserror &= ft_parse_portal(result, line, index);
		if (!iserror)
			return (0);
		iserror = 1;
		free(line);
	}
	return (1);
}
