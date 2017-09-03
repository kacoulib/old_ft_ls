/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 17:38:48 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/03 17:39:06 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_display_folder(t_file *file, int l_len[])
{
	while (file && ft_display_single(file, l_len))
		file = file->next;
	return (1);
}

int			ft_display_folder_files(t_file *folder, int l_len[])
{
	t_file	*tmp;
	int		i;

	tmp = folder;
	i = 0;
	while (tmp)
	{
		if (tmp->type != 4 && ++i)
			ft_display_single(tmp, l_len);
		tmp = tmp->next;
	}
	return (i);
}

int			ft_display_single(t_file *file, int l_len[])
{
	int		i;
	char	*tmp;

	if (ft_indexof(g_flags, 'l') > -1 && file->type != -1)
	{
		i = -1;
		while (file->l[++i] && l_len[i])
		{
			if (i == 4)
				tmp = ft_padding(file->l[i],
					(l_len[i] - ft_strlen(file->l[i])) + 1, 'r');
			else
				tmp = ft_padding(file->l[i],
					(l_len[i] - ft_strlen(file->l[i])) + 1, 'l');
			ft_putstr(ft_strjoin(tmp, " "));
		}
	}
	ft_display_color(file);
	return (1);
}

int			ft_display_color(t_file *file)
{
	char	**tmp;

	if (file->type == 10)
	{
		tmp = ft_strsplit(file->name, ' ');
		ft_putfile(tmp[0], file->type, tmp[1]);
	}
	else if ((file->sb->st_mode & S_IWOTH))
		ft_putfile(file->name, 32, NULL);
	else if ((file->sb->st_mode & S_IXOTH) && file->type != 4)
		ft_putfile(file->name, 16, NULL);
	else
		ft_putfile(file->name, file->type, NULL);
	ft_putchar('\n');
	return (1);
}
