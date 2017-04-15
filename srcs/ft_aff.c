/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 01:45:00 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/21 01:45:00 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <gfx.h>
#include <raytracer.h>

void		ft_render(t_env *e)
{
	int		old;
	int		thread_ret;

	e->worker_stop = 0;
	e->worker = SDL_CreateThread(ft_aff, "rt_worker", e);
	usleep(2000);
	old = e->rendering_preview;
	if (e->set->display == LEGACY)
	{
		while (e->y < e->set->height && e->x < e->set->width && e->worker
				 && !(e->worker_stop))
		{
			if (old && !e->rendering_preview)
			{
				gfx_display_image(e->gfx, 0, 0, e->gfx->buff[e->gfx->act]);
				old = e->rendering_preview;
			}
			loading_bar(e, (float)(e->y * 100) / e->set->height,
						int_to_tcolor(0x1010A0), int_to_tcolor(0));
			event_poll(e);
			usleep(16000);
		}
	}
	else if (e->set->threads <= 1)
	{
		usleep(42000);
		while (e->remaining && !(e->worker_stop))
		{
			gfx_display_image(e->gfx, 0, 0, e->gfx->buff[e->gfx->act]);
			event_poll(e);
			usleep(16000);
		}
	}
	if (!(e->worker_stop))
		SDL_WaitThread(e->worker, &thread_ret);
	gfx_display_image(e->gfx, 0, 0, e->gfx->buff[e->gfx->act]);
	e->worker = 0;
	e->worker_stop = 1;
}

int			ft_aff(void *data)
{
	t_env	*e;

	e = (t_env *)data;
	if (e->set->preview)
		ft_aff_quick(e, e->obj);
	if (e->set->display == PROGRESSIVE)
		ft_aff_random(e, e->obj, DEF_MULTITHREAD);
	else if (e->set->threads > 1)
		ft_aff_multithread(e, e->obj);
	else
	{
		e->y = 0;
		while (e->y < e->set->height)
		{
			e->x = 0;
			while (e->x < e->set->width)
			{
				if (e->worker_stop)
					return (0);
				fill_pixel(e, e->obj);
				++e->x;
			}
			++e->y;
			change_cam(e);//load_add_line(e->load_bar, (e->y * 200 - 1) / e->set->height, 0x1010A0);1
		}
	}
	return (0);
}

void		ft_aff_quick(t_env *e, t_obj *obj)// ecran noir ???
{
	t_color	color;

	e->rendering_preview = 1;
	//reset display
	e->y = 0;
	while (e->y < e->set->height)
	{
		e->x = 0;
		while (e->x < e->set->width)
		{
			if (e->worker_stop)
				return;
			color = compute_color(e, obj, e->set->deph);
			color.a = 255;
			gfx_pixel_put_to_image(e->gfx->buff[e->gfx->act],
										(int)e->x, (int)e->y, color);
			e->x += 2;
		}
		e->y += 2;
	}
	e->rendering_preview = 0;
//	gfx_display_image(e->gfx, 0, 0, e->gfx->buff[e->gfx->act]);
}

void		ft_aff_random(t_env *e, t_obj *obj, int multithread)
{
	int				*map;
	int				res;
	int				pos;
//	int				i;

	if (e->set->threads > 1 && multithread)
	{
		ft_aff_multithread(e, e->obj);
		return ;
	}
	res = e->set->width * e->set->height;
	map = init_map(res);
	e->remaining = res;
//	i = 0;
	while (e->remaining > 0)
	{
		if (e->worker_stop)
			return;
		pos = get_pos(map, res, &(e->remaining));
		e->y = pos / e->set->width;
		e->x = pos % e->set->width;
		fill_pixel(e, obj);
//		if (!(++i % 2000))
//			expose_hook(e);
	}
	ft_printf("Rendering finished\n");
}

void		ft_aff_rand(t_th_data *a, t_env *e)
{
	int		pos;

	srand(time(NULL));
	while (a->nb > 0)
	{
		pos = rand() % a->res;
		while (!a->map[pos] && a->nb)
		{
			++pos;
			if (pos > a->res)
				pos = 0;
		}
		if (a->nb)
		{
			a->map[pos] = 0;
			e->y = pos / e->set->width;
			e->x = pos % e->set->width;
			fill_pixel(e, e->obj);
			while (pthread_mutex_lock(&(a->mutex)) != 0)
				;
			--a->nb;
			pthread_mutex_unlock(&(a->mutex));
		}
	}
	free(e);
}

void		ft_aff_multithread(t_env *e, t_obj *obj)
{
	int			i;
	int			j;
	t_th_data	data;

	i = 99;
	j = 0;
	(void)obj;
	data.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	data.res = e->set->width * e->set->height;
	data.nb = data.res;
	data.map = init_map(data.res);
	data.e = e;
	launch_threads(&data);
	while (data.nb)
	{
		if (e->worker_stop)
			return;//kill threads before
		++j;
		if (i != (data.nb * 100) / data.res)
		{
			ft_printf("%sRendering: %d", (i != 0 ? "\r" : ""), 100 - i);
			i = (data.nb * 100) / data.res;
		}
		if (e->set->display == PROGRESSIVE)
			gfx_display_image(e->gfx, 0, 0, e->gfx->buff[e->gfx->act]);//fonction lente
		else
		{
			loading_bar(e, 200.0 - (float)(data.nb * 200) / (float)data.res,
						int_to_tcolor(0x1010A0), int_to_tcolor(0));
		}
		event_poll(e);
		usleep(10000);
	}
//	gfx_display_image(e->gfx, 0, 0, e->gfx->buff[e->gfx->act]);
	ft_printf("\nRendering finished\n");
}
