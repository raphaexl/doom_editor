/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:48:23 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 17:33:58 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H
# define SCR_WIDTH 1240
# define SCR_HEIGHT 720
# define GAME_W 800
# define GAME_H 500
# define EDIT_W 800
# define EDIT_H 500
# define G_START_X 100
# define G_START_Y 50
# define E_START_X 100
# define E_START_Y 50
# define TILE_W 64
# define TILE_H 64
# define RGB_B(c) (c & 255)
# define RGB_G(c) ((c >> 8) & 255)
# define RGB_R(c) ((c >> 16) & 255)
# define RGB_A(c) ((c >> 24) & 255)
# define KEY(e) e.key.keysym.sym
# define DEBUG 1

# define PROP_TRANSPARENT 1
# define PROP_TRAVERSABLE 2
# define PROP_FIXED 4
# define HALF_PI 1.57079632679
# define ERROR 0
# define SUCCESS 1
# define TYPE_NONE 0
# define TYPE_WALL 1
# define TYPE_PORTAL 2
# define TYPE_OBJECT 3
# define GET_PORT(x) ((t_portal *)x->object)
# define GET_WALL(x) ((t_wall *)x->object)
# define GET_OBJ(x) ((t_object *)x->object)

# define CONFIG_IMAGE_WIDTH GAME_W
# define CONFIG_IMAGE_HEIGHT GAME_H
# define DEFAULT_WALLHEIGHT 1024
# define CONFIG_RES_RATIO 2
# define PROJECTION_DISTANCE 600
# define PROJECTION_PLANE CONFIG_IMAGE_WIDTH
# define MAX_RAY_DIST INFINITY
# define PLAYER_HEIGHT DEFAULT_WALLHEIGHT / 2
//Displayable number of texture (visible);
# define N_TEX_DISP 10

# define PLAYER_HEAD_MARGIN 50
# define CONFIG_GRAVITY 250
# define MIN_PLAYER_SPEED 0.1
# define PLAYER_CROUCH_SPEED 1500
# define PLAYER_HEAD_SPEED 0.003
# define PLAYER_VELOCITY 500
# define PLAYER_FRICTION 5
# define PLAYER_JUMP 120

# define BUTTON_W 50
# define BUTTON_H 25
# define BUTTON_FSIZE 10
# define BUTTON_NSIZE 5
# define BUTTON_FONT ("data/fonts/Roboto-Condensed.ttf")
# define ANGELINA_FONT ("data/fonts/angelina.TTF")
# define B_X_MARGIN 10
# define B_Y_MARGIN 0
# define B_X_START 100
# define B_Y_START 2

# define SCALE 20

# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_mixer.h"
# include "libft.h"
# include "linked_list.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
# define B_ENDIAN 1
# define RMASK 0xFF000000
# define GMASK 0x00FF0000
# define BMASK 0x0000FF00
# define AMASK 0x000000FF
# else
# define B_ENDIAN 0
# define RMASK 0x000000FF
# define GMASK 0x0000FF00
# define BMASK 0x00FF0000
# define AMASK 0xFF000000
# endif

#endif
