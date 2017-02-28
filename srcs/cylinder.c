/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 18:06:04 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/07 14:23:30 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

void		trace_cylinder(t_obj *obj, t_vector o, t_vector v)
{
	t_equation	eq;

	rotate_vector2(&o, &(obj->ang));
	rotate_vector2(&v, &(obj->ang));
	sub_vector(&o, &(obj->pos));
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
//	(void)obj;
	not_ang.x = -obj->ang.x;
	not_ang.y = -obj->ang.y;
	not_ang.z = 0;
	*n = obj->n;
	/*n->x = o->x - obj->pos.x;
	n->y = o->y - obj->pos.y;
	n->z = 0;*/
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
		rotate_vector2(&eq->v, &obj->ang);
		rotate_vector2(&eq->o, &obj->ang);
		sub_vector(&eq->o, &obj->pos);
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

void		neg_cylinder_fill(t_obj *obj, t_equation *eq)
{
	float		save;
	t_vector	point;
	t_vector	not_ang;

	save = 0;
	not_ang = obj->ang;
	not_vec(&not_ang);
	obj->dst = 1e8;
	neg_cylinder(obj, eq);
	if (eq->delta > 0)
	{
		trace_cylinder(obj, eq->o, eq->v);
		if (obj->x1 > obj->x2)
		{
			save = obj->x1;
			obj->x1 = obj->x2;
			obj->x2 = save;
		}
		if (eq->obj->type & (SPHERE))
		{
			point.x = eq->v.x * obj->x1 + eq->o.x + obj->pos.x;
			point.y = eq->v.y * obj->x1 + eq->o.y + obj->pos.y;
			point.z = eq->v.z * obj->x1 + eq->o.z + obj->pos.z;
			if (vec_len(&point) < eq->obj->size)
				obj->dst = obj->x1;
			point.x = eq->v.x * obj->x2 + eq->o.x + obj->pos.x;
			point.y = eq->v.y * obj->x2 + eq->o.y + obj->pos.y;
			point.z = eq->v.z * obj->x2 + eq->o.z + obj->pos.z;
			if (vec_len(&point) < eq->obj->size)
				obj->dst = obj->x2;
			else
				obj->dst = 1e8;
		}
/*		else if (eq->obj->type & (CYLINDER))
		{
			point.x = eq->v.x * obj->x1 + eq->o.x + obj->pos.x;
			point.y = eq->v.y * obj->x1 + eq->o.y + obj->pos.y;
			point.z = 0;
			if (vec_len(&point) < eq->obj->size)
				obj->dst = obj->x1;
			point.x = eq->v.x * obj->x2 + eq->o.x + obj->pos.x;
			point.y = eq->v.y * obj->x2 + eq->o.y + obj->pos.y;
			if (obj->x2 < obj->x1 && vec_len(&point) < eq->obj->size)
				obj->dst = obj->x2;
			else if (obj->dst != obj->x1)
				obj->dst = 1e8;
		}*/
		else
			obj->dst = 1e8;
	}
	else
		obj->dst = 1e8;
}
