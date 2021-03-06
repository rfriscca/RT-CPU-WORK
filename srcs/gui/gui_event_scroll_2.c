/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_event_scroll_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 04:00:03 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	event_scroll_mouse_over(SDL_Event event, t_gui *gui, t_scroll *scroll)
{
	int	motion;

	if ((event.motion.x >= scroll->dest.x) &&
	(event.motion.x <= scroll->dest.x + scroll->dest.w) &&
	(event.motion.y >= scroll->dest.y) &&
	(event.motion.y <= scroll->dest.y + scroll->dest.h))
	{
		motion = (event.motion.y - scroll->dest.y
		+ (scroll->mod * GUI_LIST_STEP)) / GUI_LIST_STEP;
		gui_scroll_write_list(gui, scroll, motion);
	}
}

void	event_scroll_down(t_gui *gui, t_scroll *scroll)
{
	if (scroll->mod < scroll->nb_value - GUI_SCROLL_MAX_SHOWN)
	{
		scroll->mod++;
		gui_widget_texture_get_bmp(scroll, "scroll_white.bmp");
		gui_widget_display(scroll);
		gui_scroll_write_list(gui, scroll, -1);
	}
}

void	event_scroll_up(t_gui *gui, t_scroll *scroll)
{
	if (scroll->mod > 0)
	{
		scroll->mod--;
		gui_widget_texture_get_bmp(scroll, "scroll_white.bmp");
		gui_widget_display(scroll);
		gui_scroll_write_list(gui, scroll, -1);
	}
}

int		event_scroll_mouse_wheel(SDL_Event event, t_gui *gui)
{
	t_scroll	*tmp;

	if (WIDGET && *(int *)WIDGET == SCL)
	{
		tmp = WIDGET;
		if (event.wheel.y > 0)
			event_scroll_up(gui, tmp);
		else if (event.wheel.y < 0)
			event_scroll_down(gui, tmp);
		else
		{
			tmp = NULL;
			return (0);
		}
		tmp = NULL;
		return (1);
	}
	return (0);
}
