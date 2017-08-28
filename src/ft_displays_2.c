/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_displays_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 18:50:15 by kacoulib          #+#    #+#             */
/*   Updated: 2017/02/20 18:50:20 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_display_color(t_file *file)
{
	if (file->type == 12 && file->l[0] && file->l[0][10] == ' ')
		ft_putstr(SETCOLOR ? ANSI_COLOR_BLACK : "");
	else if (file->type == 0)
		ft_putstr(SETCOLOR ? ANSI_COLOR_RED : "");
	else if (file->type == 4)
		ft_putstr(SETCOLOR ? ANSI_COLOR_CYAN : "");
	else if (file->type == 10)
	{
		ft_putstr(SETCOLOR ? ANSI_COLOR_MAGENTA : "");
		if (ft_indexof(g_flags, 'l') > -1 && ft_display_color_extra(file))
			return (1);
	}
	ft_putstr(file->name);
	ft_putendl(SETCOLOR ? ANSI_COLOR_RESET : "");
	return (1);
}

int			ft_display_color_extra(t_file *file)
{
	char	**r;

	r = ft_strsplit(file->name, ' ');
	ft_putstr(r[0]);
	ft_putstr(SETCOLOR ? ANSI_COLOR_RESET : "");
	ft_putstr(" -> ");
	ft_putstr(r[1]);
	ft_putendl(SETCOLOR ? ANSI_COLOR_RESET : "");
	return (1);
}

int			ft_print(char *s1, char *s2, char *s3, char *s4)
{
	char	*tmp;

	tmp = NULL;
	if (s1 && s2)
		tmp = ft_strjoin(s1, s2);
	if (s3)
		tmp = ft_strjoin(tmp, s3);
	if (s4)
		tmp = ft_strjoin(tmp, s4);
	if (tmp)
	{
		ft_putendl(tmp);
		free(tmp);
	}
	return (1);
}
