/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 01:39:21 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/03 13:28:33 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <raytracer.h>

t_obj		*copy_obj_elem_2(t_obj *res, t_obj *obj)
{
	res->cap1 = obj->cap1;
	res->cap2 = obj->cap2;
	res->surface = obj->surface;
	res->nm_surface = obj->nm_surface;
	res->tex_surface = obj->tex_surface;
	res->def = obj->def;
	res->n = obj->n;
	res->x1 = obj->x1;
	res->x2 = obj->x2;
	res->texture = obj->texture ? ft_strdup(obj->texture) : 0;
	res->procedural = obj->procedural ? ft_strdup(obj->procedural) : 0;
	res->normalmap = obj->normalmap ? ft_strdup(obj->normalmap) : 0;
	res->compose = obj->compose ? copy_obj(obj->compose) : 0;
	return (res);
}

t_obj		*copy_obj_elem(t_obj *obj)
{
	t_obj	*res;

	if (!(res = (t_obj *)malloc(sizeof(t_obj))))
		error(1);
	res->type = obj->type;
	res->func = obj->func;
	res->normale = obj->normale;
	res->negative = obj->negative;
	res->pos = obj->pos;
	res->ang = obj->ang;
	res->exp = obj->exp;
	res->color = obj->color;
	res->color2 = obj->color2;
	res->color3 = obj->color3;
	res->color_refract = obj->color_refract;
	res->size = obj->size;
	res->mod = obj->mod;
	res->reflect_k = obj->reflect_k;
	res->transparency = obj->transparency;
	res->refract_ind = obj->refract_ind;
	res->dst = obj->dst;
	return (copy_obj_elem_2(res, obj));
}

t_obj		*copy_obj(t_obj *obj)
{
	t_obj	*act;
	t_obj	*res;

	if (!obj)
		return (0);
	res = copy_obj_elem(obj);
	act = res;
	obj = obj->next;
	while (obj)
	{
		act->next = copy_obj_elem(obj);
		obj = obj->next;
		act = act->next;
	}
	act->next = NULL;
	return (res);
}

void		copy_noise(t_env *res, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < NOISE_HEIGHT)
	{
		while (j < NOISE_WIDTH)
		{
			res->noise[i][j] = env->noise[i][j];
			++j;
		}
		j = 0;
		++i;
	}
}

t_env		*copy_env(t_env *e)
{
	t_env *res;

	if (!(res = (t_env *)malloc(sizeof(t_env))))
		error(1);
	res->gfx = e->gfx;
	res->set = e->set;
	res->obj = copy_obj(e->obj);
	res->neg_obj = copy_obj(e->neg_obj);
	res->light = e->light;
	res->x = e->x;
	res->y = e->y;
	res->last_dst = e->last_dst;
	res->worker = e->worker;
	res->worker_stop = e->worker_stop;
	res->rendering_preview = e->rendering_preview;
	res->file = ft_strdup(e->file);
	res->last_refract = e->last_refract;
	res->remaining = e->remaining;
	res->render_progression = e->render_progression;
	copy_noise(res, e);
	res->inside_obj = e->inside_obj;
	return (res);
}
