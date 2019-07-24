/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:13:13 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 22:00:59 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "graphic_engine.h"

int			ft_min(int a, int b);
int			ft_max(int a, int b);
int			ft_limit(int value, int min, int max);
int			ft_modulus(int n, int m);
int			ft_is_inrange(int value, int min, int max);

t_wall		*ft_new_wall(t_point p1, t_point p2, Uint32 texture, Uint32 properties);
t_portal	*ft_new_portal(t_point p1, t_point p2, t_sector *dest, Uint32 propr);
t_object	*ft_new_object(t_point pos, Uint32 rad, Uint32 tex, Uint32 height);
t_sector	*ft_new_sector(int floor, int ceil, int floor_tex, int ceil_tex);
t_player	*ft_new_player(t_object *object, t_sector *sector,
				int cam_height, int head_angle);

t_sector	*ft_load_sectors(const char *filename, t_game *map);
int					ft_load_sector_data(t_sector *result, int fd);
t_texture			*ft_load_texture(char *filename);

void		ft_player_apply_mvt(t_player *p, double time);
void		ft_player_process_mvt(t_player *p, t_input *in);
void		ft_player_update_event(t_player *p, t_input *in, double delta_time);

void	ft_raycast(t_graphic_render	*env);
void	ft_iter_ray(t_raycast *raygen);
void	ft_init_raycasting(t_raycast *raygen, double angle);
void	ft_intersect_ray(t_graphic_render *env, t_raycast *raygen, t_sector *sec,
				int x);

t_vector	ft_vector_from_angle(double	size, double angle);
double		ft_vector_size(t_vector *vector);
double		ft_vector_distance(t_point	p1, t_vector p2);
void		ft_normalise_vector(t_vector *vector);

void		ft_player_behave(t_player *player, t_game *game);
int			ft_keyboard_handling(t_game *game);

t_button	*ft_button_new(SDL_Renderer	*rend, char	*msg, Uint32 color);
void		ft_button_push_back(t_button **lst, t_button *nw);
void		ft_button_remove(t_button **lst, int id);
void		ft_button_clean(t_button **lst);

t_sector	*ft_sector_new(SDL_Renderer	*rend, char	*msg, Uint32 color);
void		ft_sector_push_back(t_sector **lst, t_sector *nw);
void		ft_sector_remove(t_sector **lst, int id);
void		ft_sector_clean(t_sector **lst);

t_entry		*ft_entry_new(SDL_Renderer	*rend, char	*msg, Uint32 color);
void		ft_entry_push_back(t_entry **lst, t_entry *nw);
void		ft_entry_remove(t_entry **lst, int id);
void		ft_entry_clean(t_entry **lst);
#endif
