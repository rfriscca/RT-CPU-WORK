/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_freetxt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 10:48:42 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_parse_freetxt_suite(t_freetxt *freetxt, char **tmp)
{
	char	**tmp2;

	tmp2 = NULL;
	if (!CMP(tmp[0], "\t\ttag"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		freetxt->tag = ft_strdup(tmp2[1]);
	}
	else if (!CMP(tmp[0], "\t\ttxt"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		freetxt->txt->content = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_carray(&tmp2, 2);
}

t_freetxt	*gui_parse_freetxt(int fd, int nb)
{
	t_freetxt	*freetxt;
	char		**tmp;
	char		*line;

	freetxt = gui_freetxt_init();
	while (nb > 0)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!CMP(tmp[0], "\t\tx"))
			freetxt->dest.x = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\t\ty"))
			freetxt->dest.y = ft_atoi(tmp[1]);
		else
			gui_parse_freetxt_suite(freetxt, tmp);
		gui_free_carray(&tmp, 2);
		gui_free_str(&line);
		nb--;
	}
	return (freetxt);
}
