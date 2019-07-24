/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 14:28:45 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/22 14:07:05 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/input.h"

void	ft_event_key_down(SDL_Event *e, t_input *in)
{
	int			len;

	if (e->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		in->quit = SDL_TRUE;
	else if (e->key.keysym.scancode == SDL_SCANCODE_BACKSPACE && (len = ft_strlen(in->text)))
	{
		in->text[len - 1] = '\0';
		in->render_text = 1;
	}
	else if (e->key.keysym.scancode == SDL_SCANCODE_C && (SDL_GetModState() & KMOD_CTRL))
		SDL_SetClipboardText(in->text);
	else if (e->key.keysym.scancode == SDL_SCANCODE_V && (SDL_GetModState() & KMOD_CTRL))
	{
		in->text = ft_strjoin(in->text, SDL_GetClipboardText());
		in->render_text = 1;
	}
}

int		ft_event_edition(t_input *in)
{
	SDL_Event	e;

	SDL_StartTextInput();
	in->render_text = 0;
	SDL_GetMouseState(&in->mousex, &in->mousey);
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			in->quit = SDL_TRUE;
		else if (e.type == SDL_KEYDOWN)
			ft_event_key_down(&e, in);
		else if (e.type == SDL_TEXTINPUT)
		{
			if (!(((e.text.text[0] == 'c' || e.text.text[0] == 'C') ||
							(e.text.text[0] == 'v' || e.text.text[0] == 'V')) &&
						(SDL_GetModState() & KMOD_CTRL)))
			{
				in->text = ft_strjoin(in->text, e.text.text);
				in->render_text = 1;
			}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
			in->mouse[e.button.button] = SDL_TRUE;
		else if (e.type == SDL_MOUSEBUTTONUP)
			in->mouse[e.button.button] = SDL_FALSE;
	}
	SDL_StopTextInput();
	return (in->render_text);
}
