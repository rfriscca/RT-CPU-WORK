/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 18:06:04 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/05 12:24:06 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

void		trace_cylinder(t_obj *obj, t_vector o, t_vector v)
{
	t_equation	eq;

	sub_vector(&o, &(obj->pos));
	rotate_vector2(&o, &(obj->ang));
	rotate_vector2(&v, &(obj->ang));
	exp_compute(&o, &(obj->exp));
	eq.a = powf(v.x, 2) + powf(v.y, 2);
	eq.b = 2 * (o.x * v.x + o.y * v.y);
	eq.c = powf(o.x, 2) + powf(o.y, 2) - powf(obj->size, 2);
	eq.delta = powf(eq.b, 2) - 4 * eq.a * eq.c;
	eq.obj = obj;
	eq.v = v;
	eq.o = o;
	obj->dst = solve_equation(&eq);
	obj->n.x = v.x * obj->dst + o.x;
	obj->n.y = v.y * obj->dst + o.y;
	obj->n.z = 0;
}

void		cylinder_normale(t_vector *n, t_vector *o, t_obj *obj)
{
	float		k;
	t_vector	not_ang;

	(void)o;
	not_ang.x = -obj->ang.x;
	not_ang.y = -obj->ang.y;
	not_ang.z = 0;
	*n = obj->n;
	k = sqrt(n->x * n->x + n->y * n->y + n->z * n->z);
	n->x /= k;
	n->y /= k;
	rotate_vector2(n, &not_ang);
}

void		neg_cylinder(t_obj *obj, t_equation *eq)
{
	t_vector	point;

	if (eq->delta >= 0)
	{
		sub_vector(&eq->o, &obj->pos);
		rotate_vector2(&eq->v, &obj->ang);
		rotate_vector2(&eq->o, &obj->ang);
		point.x = eq->v.x * eq->x1 + eq->o.x - obj->pos.x;
		point.y = eq->v.y * eq->x1 + eq->o.y - obj->pos.y;
		point.z = 0;
		if (vec_len(&point) < obj->size)
			eq->x1 = 1e8;
		point.x = eq->v.x * eq->x2 + eq->o.x - obj->pos.x;
		point.y = eq->v.y * eq->x2 + eq->o.y - obj->pos.y;
		point.z = 0;
		if (vec_len(&point) < obj->size)
			eq->x2 = 1e8;
	}
}
