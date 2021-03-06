/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <rdieulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/11 18:49:57 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include <parser.h>

char	*gui_old_path(char *path)
{
	char	**split;
	char	*old;
	char	*tmp;

	split = ft_strsplit(path, '.');
	tmp = ft_strjoin("cp ", path);
	old = ft_strjoin(tmp, " ");
	gui_free_str(&tmp);
	tmp = ft_strjoin(old, split[0]);
	gui_free_str(&old);
	old = ft_strjoin(tmp, ".old");
	gui_free_str(&tmp);
	gui_free_carray(&split, 2);
	return (old);
}

char	*gui_new_path(char *path)
{
	char	*new;
	char	*tmp;

	tmp = ft_strjoin("rm ", path);
	new = ft_strjoin(tmp, " |");
	gui_free_str(&tmp);
	tmp = ft_strjoin(new, "mv ");
	gui_free_str(&new);
	new = ft_strjoin(tmp, "scene/tmpsave.rts");
	gui_free_str(&tmp);
	tmp = ft_strjoin(new, " ");
	gui_free_str(&new);
	new = ft_strjoin(tmp, path);
	gui_free_str(&tmp);
	return (new);
}

void	gui_save_object(t_env *e)
{
	t_gui	*gui;

	gui = get_gui();
	system(gui_old_path(e->scene));
	if (!save_scene(e))
		gui_error(15);
	system(gui_new_path(e->scene));
}
