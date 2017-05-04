/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_event_gauge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/06 18:03:35 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

int		event_is_param_gauge(SDL_Event event, t_gui *gui, t_env *e)
{
	int	i;

	i = 0;
	while (i < PARAM->gauge_qt)
	{
		if ((HIT.x >= PARAM_GAU->dest.x) && (HIT.y >= PARAM_GAU->dest.y) &&
		(HIT.x <= PARAM_GAU->dest.x + PARAM_GAU->dest.w) &&
		(HIT.y <= PARAM_GAU->dest.y + PARAM_GAU->dest.h))
		{
			PARAM_GAU_C->dest.x = event.button.x - (PARAM_GAU_C->dest.w / 2);
			PARAM_GAU->active_value = (PARAM_GAU_C->dest.x - PARAM_GAU->dest.x)
			+ 5;
			PARAM_GAU->active_value = gui_gauge_get_norm(PARAM_GAU);
			gui_main_refresh(gui);
			if (!CMP(PARAM_GAU->tag, "LUM"))
				e->set->luminosity = PARAM_GAU->active_value;
			if (!CMP(PARAM_GAU->tag, "CON"))
				e->set->contrast = PARAM_GAU->active_value;
			if (!CMP(PARAM_GAU->tag, "LUM") || !CMP(PARAM_GAU->tag, "CON"))
				posttraitment(e);
			return (1);
		}
		i++;
	}
	return (0);
}

int		event_is_gauge(SDL_Event event, t_gui *gui, t_env *e)
{
	if (PARAM && PARAM->active == 1)
		return (event_is_param_gauge(event, gui, e));
	return (0);
}
