/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 16:06:23 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/11 12:17:30 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>
#include <stdlib.h>

int		parse_dis(t_item *it, t_vector *v, int i, void (*f)(t_vector *, char *))
{
	while (ft_strchr(it->set[i + 1], ',') != NULL)
		f(v, it->set[++i]);
	f(v, it->set[++i]);
	return (i);
}

void	parse_object_other(t_obj *obj, char *str)
{
	if (!ft_strncmp(str, "\"reflect_k\"", 11))
		obj->reflect_k = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"transparency\"", 11))
		obj->transparency = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"refract_ind\"", 13))
		obj->refract_ind = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"negative\"", 10))
	{
		obj->negative = (!ft_strncmp(get_value(str), "1", 1)
						|| !ft_strncmp(get_value(str), "true", 4));
	}
	else if (!ft_strncmp(str, "\"texture\"", 9) && ft_strchr(str, ','))
		obj->texture = ft_strtrim_coma(get_value(str));
	else if (!ft_strncmp(str, "\"texture\"", 9) && !ft_strchr(str, ','))
		obj->texture = ft_strdup(get_value(str));
	else if (!ft_strncmp(str, "\"procedural\"", 12) && ft_strchr(str, ','))
		obj->procedural = ft_strtrim_coma(get_value(str));
	else if (!ft_strncmp(str, "\"procedural\"", 12) && !ft_strchr(str, ','))
		obj->procedural = ft_strdup(get_value(str));
	else if (!ft_strncmp(str, "\"normalmap\"", 11) && ft_strchr(str, ','))
		obj->normalmap = ft_strtrim_coma(get_value(str));
	else if (!ft_strncmp(str, "\"normalmap\"", 11) && !ft_strchr(str, ','))
		obj->normalmap = ft_strdup(get_value(str));
	else
		ft_printf("\033[31m%s Not found\n\033[0m", str);
}

void	parse_obj_exp(t_vector *v, char *str)
{
	if (!ft_strncmp(str, "\"x\"", 3))
		v->x = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"y\"", 3))
		v->y = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"z\"", 3))
		v->z = ft_atof(get_value(str));
	else
	{
		ft_printf("Bad name in Exp\n");
		exit(EXIT_SUCCESS);
	}
}

void	parse_obj_color(t_obj *obj, char *str)
{
	if (!ft_strncmp(str, "\"color2\"", 8))
		obj->color2 = get_color(get_value(str));
	else if (!ft_strncmp(str, "\"color3\"", 8))
		obj->color3 = get_color(get_value(str));
	else if (!ft_strncmp(str, "\"color_refract\"", 15))
		obj->color_refract = get_color(get_value(str));
	else if (!ft_strncmp(str, "\"color\"", 7))
		obj->color = get_color(get_value(str));
}
