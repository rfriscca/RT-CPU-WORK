#include <gui.h>

void	event_poll(t_env *e)
{
	libxmlx_poll(e->gfx);
	event(e, e->gfx->event);
}

void	wait_event(t_env *e)
{
	libxmlx_loop(e->gfx);
	event(e, e->gfx->event);
}

void	event_mouse_wheel(SDL_Event event, t_gui *gui)
{
	if (!event_scroll_mouse_wheel(event, gui))
		return;
}

void	event_mouse_click(SDL_Event event, t_env *env, t_gui *gui)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		if (!event_is_scroll(event, gui))
			if (!event_is_checkbox(event, gui))
				if (!event_is_button(event, env, gui))
					if (!event_is_textbox(event, gui))
						if (gui->widget_active)
							event_widget_deselect(gui);
	}
}

static int	event_keydown(SDL_Event event, t_env *env, t_gui *gui)
{
	static int	console_mode = 0;

	if (event.window.windowID == env->gfx->winID)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			libxmlx_exit(env->gfx, 0);
		if (event.key.keysym.sym == SDLK_BACKQUOTE)
		{
			console_mode = !console_mode;
			printf("Console mode: %s\n", console_mode ? "ON" : "OFF");
		}
		if (console_mode)
			console_mode = rt_console(event.key.keysym.sym, env);
	}
	if (gui->widget_active && (event.window.windowID == gui->winID))
		event_textbox_insert(event, gui, gui->widget_active);
	return (0);
}

void	event_mouse_motion(SDL_Event event, t_gui *gui)
{
	t_scroll	*tmp;

	if (WIDGET && *(int *)WIDGET == SCL)
	{
		tmp = WIDGET;
		event_scroll_mouse_over(event, gui, tmp);
	}
}

int		event(t_env *env, SDL_Event event)
{
	t_gui *gui;

	gui = get_gui();
	if (event.type == SDL_WINDOWEVENT)
		if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			libxmlx_exit(env->gfx, 0);
	if (event.type == SDL_KEYDOWN)
		event_keydown(event, env, gui);
	else
	{
		if (event.window.windowID == gui->winID)
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
				event_mouse_click(event, env, gui);
			if (event.type == SDL_MOUSEWHEEL)
				event_mouse_wheel(event, gui);
			if (event.type == SDL_MOUSEMOTION)
				event_mouse_motion(event, gui);
		}
		SDL_RenderPresent(gui->img);
	}
	return (0);
}
