/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 01:41:47 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/21 01:41:48 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <raytracer.h>

void		*thread_aff(void *arg)
{
	t_th_data	*a;
	t_env		*e;

	a = (t_th_data *)arg;
	e = copy_env(a->e);
	ft_aff_rand(a, e);
	pthread_exit(NULL);
}

void		launch_threads(t_th_data *data)
{
	int			i;
	pthread_t	thread_ptr;

	i = -1;
	while (++i < data->e->set->threads)
	{
		if (pthread_create(&thread_ptr, NULL, thread_aff, data))
			return ;
	}
}