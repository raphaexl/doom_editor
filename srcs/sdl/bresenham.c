/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 16:01:30 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 16:49:20 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	ft_sdl_draw_octant1(t_img *img, t_point p, t_point q, Uint32 c)
{
	t_point		dp;
	t_point		pincr;
	int			error;
	int			i;

	i = -1;
	pincr.x = p.x < q.x ? 1 : -1;
	pincr.y = p.y < q.y ? 1 : -1;
	dp.x = abs(q.x - p.x);
	dp.y = abs(q.y - p.y);
	error = dp.x / 2;
	while (++i <= dp.x)
	{
		p.x += pincr.x;
		error += dp.y;
		if (error > dp.x)
		{
			error -= dp.x;
			p.y += pincr.y;
		}
		ft_sdl_put_pixel(img, p.x, p.y, c);
	}
}

void		ft_sdl_draw_octant2(t_img *img, t_point p, t_point q, Uint32 c)
{
	t_point		dp;
	t_point		pincr;
	int			error;
	int			i;

	pincr.x = (p.x < q.x) ? 1 : -1;
	pincr.y = (p.y < q.y) ? 1 : -1;
	dp.x = abs(q.x - p.x);
	dp.y = abs(q.y - p.y);
	error = dp.y / 2;
	i = -1;
	while (++i <= dp.y)
	{
		p.y += pincr.y;
		error += dp.x;
		if (error > dp.y)
		{
			error -= dp.y;
			p.x += pincr.x;
		}
		ft_sdl_put_pixel(img, p.x, p.y, c);
	}
}

void		ft_sdl_draw_line(t_img *img, t_point p, t_point q, Uint32 c)
{
	ft_sdl_put_pixel(img, p.x, p.y, c);
	ft_sdl_put_pixel(img, q.x, q.y, c);
	if (abs(q.x - p.x) >= abs(q.y - p.y))
		ft_sdl_draw_octant1(img, p, q, c);
	else
		ft_sdl_draw_octant2(img, p, q, c);
}

void		ft_sdl_draw_disc(t_img *img, t_point co, int radius, Uint32 col)
{
	int		d;
	int		x;
	int		y;

	y = radius;
	d = 3 - (radius << 1);
	x = -1;
	while (y >= ++x)
	{
		ft_sdl_draw_line(img, ft_point(co.x - x, co.y - y), ft_point(co.x + 1
					+ x, co.y - y), col);
		ft_sdl_draw_line(img, ft_point(co.x - x, co.y + y), ft_point(co.x
					+ 1 + x, co.y + y), col);
		ft_sdl_draw_line(img, ft_point(co.x - y, co.y - x), ft_point(co.x + 1
					+ y, co.y - x), col);
		ft_sdl_draw_line(img, ft_point(co.x - y, co.y + x), ft_point(co.x + 1
					+ y, co.y + x), col);
		if (d < 0)
			d = d + (x << 2) + 6;
		else
		{
			d = d + ((x - y) << 2) + 10;
			--y;
		}
	}
}

void		ft_sdl_draw_rect(t_img *img, t_rect rect, Uint32 c)
{
	int		i;
	int		j;

	i = rect.y - 1;
	while (++i < rect.y + rect.h)
	{
		j = rect.x - 1;
		while (++j < rect.x + rect.w)
			ft_sdl_put_pixel(img, j, i, c);
	}
}
