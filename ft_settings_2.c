/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 18:51:52 by kacoulib          #+#    #+#             */
/*   Updated: 2017/02/20 18:51:53 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_padding(char *s, int offset, char direction)
{
	char			*tmp;
	int				i;

	if (offset <= 0)
		return (ft_strtrim(s));
	i = (ft_strlen(s) + offset);
	if (!(tmp = (char *)malloc((sizeof(char) * i))))
		return (0);
	ft_memset(tmp, ' ', (i - 1));
	s = ft_strtrim(s);
	if (direction == 'l' && (i = -1) == -1)
		while (s[++i])
			tmp[i] = s[i];
	else
		ft_strcpy(&(tmp)[offset], s);
	return (tmp);
}

// int			ft_set_acl(t_file *file)
// {
// 	char	r[1000];

// 	return (1);
// }

int			ft_set_time(t_file *file)
{
	char	**r;
	char	**tmp;
	time_t	curtime;

	if (!(r = (char **)malloc(sizeof(char *) * 100)) ||
	!(*r = ctime(&file->sb->st_mtime)))
		return (0);
	r = ft_strsplit(*r, ' ');
	file->l[5] = r[1];
	file->l[5] = ft_strjoin(file->l[5], " ");
	file->l[5] = ft_strjoin(file->l[5],
		ft_padding(r[2], (ft_strlen(r[2]) > 1 ? 0 : 1), 'r'));
	file->l[5] = ft_strjoin(file->l[5], " ");
	tmp = r;
	if ((time(&curtime) - 15552000) > file->sb->st_mtime)
		file->l[5] = ft_strjoin(file->l[5], ft_padding(tmp[4], 1, 'r'));
	else
	{
		r = ft_strsplit(r[3], ':');
		file->l[5] = ft_strjoin(file->l[5], r[0]);
		file->l[5] = ft_strjoin(file->l[5], ":");
		file->l[5] = ft_strjoin(file->l[5], r[1]);
	}
	return (1);
}
