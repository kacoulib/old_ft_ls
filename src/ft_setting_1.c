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

t_file			*ft_init_folder(char *name, t_file *parent, t_file *prev)
{
	t_file		*file;
	struct stat	*sb;

	file = (t_file *)malloc(sizeof(t_file) + 1);
	sb = (struct stat*)malloc(sizeof(struct stat) + 1);
	if (!file || !sb)
		return (NULL);
	file->name = (name) ? ft_strdup(name) : NULL;
	file->path = NULL;
	file->info = NULL;
	file->size = 0;
	file->type = 8;
	file->sb = sb;
	file->files = NULL;
	file->parent = parent;
	file->errors = NULL;
	file->next = NULL;
	file->prev = prev;
	return (file);
}

char			*ft_padding(char *s, int offset, char direction)
{
	char		*tmp;
	int			i;

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

int				ft_push_file(t_file *head, t_file *file)
{
	t_file		*tmp;

	if (!(tmp = head))
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = file;
	file->prev = tmp;
	return (0);
}

/*
**	@param [s] Is the name of the file name that is invalid or
**				in which we don't have the permission
*/

int				ft_set_error(t_file *file, char *s, char *err)
{
	t_file		*tmp;

	if (!file || !(tmp = ft_init_folder("ft_ls: ", file, NULL)))
		return (0);
	tmp->name = ft_strdup("ft_ls: ");
	if (err && ft_strcmp(err, "wrong flag") == 0)
	{
		tmp->name = ft_strjoin(tmp->name, "illegal option -- ");
		tmp->name = ft_strjoin(tmp->name, s);
		tmp->name = ft_strjoin(tmp->name, "\nusage: ft_ls [");
		tmp->name = ft_strjoin(tmp->name, g_flags);
		tmp->name = ft_strjoin(tmp->name, "] [file ...]");
	}
	else
	{
		tmp->name = ft_freejoin(tmp->name, s);
		tmp->name = ft_freejoin(tmp->name, " : ");
		tmp->name = ft_freejoin(tmp->name, (char *)sys_errlist[errno]);
	}
	if (file->errors)
		ft_push_file(file->errors, tmp);
	else
		file->errors = tmp;
	return ((tmp->type = -1));
}

int				ft_set_params(t_file *file, char **av, int i)
{
	int			j;
	int			k;
	char		r[ft_strlen(g_flags)];

	j = 0;
	k = -1;
	ft_memset(r, '\0', ft_strlen(g_flags));
	while (av[++i] && av[i][0] == '-' && av[i][1])
	{
		while (av[i][++j] != '\0')
		{
			if (ft_indexof(g_flags, av[i][j]) < 0 || av[i][j] == '-')
			{
				ft_set_error(file, ft_strsub(av[i], j, 1), "wrong flag");
				return (-1);
			}
			if (ft_indexof(g_flags, av[i][j]) >= 0)
				if (ft_indexof(r, av[i][j]) < 0)
					r[++k] = av[i][j];
		}
		j = 0;
	}
	g_flags = ft_strdup(r);
	return (i);
}
