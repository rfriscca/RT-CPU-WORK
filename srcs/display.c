/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 23:16:16 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/22 14:42:06 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <gfx.h>
#include <raytracer.h>

void		trace_ray_lights(t_env *e, t_obj *obj, t_vector *o, t_vector *v)
{
	(void)e;
	if (obj->negative == 0 && obj->func)
		(obj->func)(obj, *o, *v);
	else
		obj->dst = 1e8;
}

void		trace_ray(t_env *e, t_obj *obj, t_vector *o, t_vector *v)
{
	(void)e;
	if (obj->func && obj->negative == 0)
		(obj->func)(obj, *o, *v);
	else
		obj->dst = 1e8;
}

void		change_cam(t_env *e)
{
	t_cam	*buff;

	if (!e->set->d3_mode)
		return ;
	buff = e->set->cam;
	e->set->cam = e->set->cam2;
	e->set->cam2 = buff;
}

void		fill_pixel(t_env *e, t_obj *obj)
{
	t_color	color;

	if (e->set->aa >= 64)
		color = aa_64(e, obj, e->set->deph);
	else if (e->set->aa >= 32)
		color = aa_32(e, obj, e->set->deph);
	else if (e->set->aa >= 16)
		color = aa_16(e, obj, e->set->deph);
	else if (e->set->aa >= 8)
		color = aa_8(e, obj, e->set->deph);
	else if (e->set->aa >= 4)
		color = aa_4(e, obj, e->set->deph);
	else if (e->set->aa >= 2)
		color = aa_2(e, obj, e->set->deph);
	else
		color = compute_color(e, obj, e->set->deph);
	color.a = 255;
	gfx_pixel_put_to_image(e->gfx->buff[BUFF_NB],
								(int)e->x, (int)e->y, color);
}

int			*init_map(int nb)
{
	int		*res;
	int		i;

	if (!(res = (int *)malloc(nb * sizeof(int))))
		error(1);
	i = -1;
	while (++i < nb)
		res[i] = 1;
	return (res);
}
