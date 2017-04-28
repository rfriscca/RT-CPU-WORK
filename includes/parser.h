/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 03:28:43 by jrouilly          #+#    #+#             */
/*   Updated: 2017/04/26 12:52:56 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <libft.h>
# include <raytracer.h>

# define MAX_PARAM		100

typedef struct		s_item
{
	char			*type;
	int				setnb;
	char			*set[MAX_PARAM];
}					t_item;

void				parse(t_env *e, char *filename);
void				aff_obj(t_obj *obj);
void				aff_settings(t_settings *set);
void				aff_light(t_light *light);
t_obj				*new_obj(void);
t_settings			*new_settings(void);
t_light				*new_light(void);
char				*ft_getfile(char *name);
t_item				*get_next_item(char **str);
int					add_next_set(t_item *item, char **file);
char				*get_value(char *str);
void				parse_pos(t_vector *v, char *str);
void				parse_ang(t_vector *v, char *str);
void				parse_obj_exp(t_obj *obj, char *str);
void				parse_obj_color(t_obj *obj, char *str);
void				parse_object_other(t_obj *obj, char *str);
void				parse_settings(t_env *e, t_item *item);
void				parse_object(t_env *e, t_item *item);
void				parse_set_cam(t_env *e, char *str);
void				parse_other_setting(t_env *e, char *str);
void				parse_set_focus(t_env *e, char *str);
void				parse_light(t_env *e, t_item *item);
int					first_chek(t_env *e, char *str);
void				code_error_parser(t_env *e, int error);
int					parse_dis(t_item *it, t_vector *v, int i, void (*f)(t_vector *, char *));

#endif
