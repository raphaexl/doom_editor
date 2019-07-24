/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 14:23:51 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 08:49:54 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
#include "structs.h"
# define KEY_UP SDL_SCANCODE_W
# define KEY_LEFT SDL_SCANCODE_A
# define KEY_RIGHT SDL_SCANCODE_D
# define KEY_DOWN SDL_SCANCODE_S
typedef	enum	e_type
{
			DEFAULT, EDITING
}				t_type;

typedef struct		s_input
{
	t_type		mode;
	char		*text;
	int			render_text;
	int			quit;
	int			focus;
	int			mousex;
	int			mousey;
	int			mousexrel;
	int			mouseyrel;
	int			ywheel;
	int			mouse[6];
	int			keys[SDL_NUM_SCANCODES];
}					t_input;
void		ft_event_normal(t_input *in);
int			ft_event_edition(t_input *in);
#endif
