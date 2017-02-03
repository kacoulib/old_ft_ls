/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:37:25 by kacoulib          #+#    #+#             */
/*   Updated: 2017/01/18 16:38:00 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char				*ft_padding(char *s, int offset, char direction)
{
	char			*tmp;
	int				i;

	if (offset <= 0)
		return (ft_strtrim(s));
	i = (ft_strlen(s) + offset);
	// printf("(%d)\n", i);
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

t_file				*ft_init_folder(char *name, t_file **parent, t_file *prev)
{
	t_file			*file;
	struct stat		*sb;

	file = (t_file *)malloc(sizeof(t_file) + 1);
	sb = (struct stat*)malloc(sizeof(struct stat) + 1);
	if (!file || !sb)
		return (NULL);
	file->name = name;
	file->path = NULL;
	file->info = NULL;
	file->size = 0;
	file->type = 8;
	file->sb = sb;
	file->files = NULL;
	file->parent = parent;
	file->next = NULL;
	file->prev = prev;
	return (file);
}

int					ft_parse_dir(t_file **file, char *name, int l[])
{
	struct dirent	*tmp;
	DIR				*dir;
	t_file			*current;
	t_file			**parent;

	if (!(dir = opendir(name)))
	{
		ft_display_error(name, 0);
		printf("error openning file %s\n", name);
		return (0);
	}
	parent = file;
	name = ft_strjoin(name, ft_strdup("/"));
	while ((tmp = readdir(dir)))
	{
		if ((tmp->d_name[0] != '.' || (ft_indexof(g_flags, 'a') >= 0) ? 1 : 0)) // if hidden file
		{
			if (!(*file) && ((*file = ft_init_folder(tmp->d_name, parent, *file))))
				current = *file;
			else if ((current->next = ft_init_folder(tmp->d_name, parent, current)))
				current = current->next;
			if (!ft_set_file(current, ft_strjoin(name, tmp->d_name), tmp->d_name, tmp->d_type))
			{
				printf("-%s\n", current->name);
				return (0);
			}
			if (tmp->d_type == 4 && ft_indexof(g_flags, 'R') >= 0)
				if (ft_strcmp(tmp->d_name, ".") != 0 && ft_strcmp(tmp->d_name, "..") != 0)
					if (!ft_parse_dir(&(current->files), ft_strjoin(name, tmp->d_name), l))
						printf("____%s\n", current->name);

		}
	}
	closedir(dir);
	return (1);
}

int					main(int ac, char **av)
{
	int				i;
	int				l_params_length[8];
	char			*folder_name;
	struct dirent	*file;
	t_file			*folder;
	char			*tmp;

	i = 0;
	folder = NULL;
	if ((i = ft_set_params(av)) < 0)
		return (ft_display_error(folder_name, 0));
	folder_name = (av[i]) ? ft_strdup(av[i]) : ft_strdup(".");
	if (!(folder = ft_init_folder(folder_name, NULL, NULL)))
		return (ft_display_error(folder_name, 0));
	ft_parse_dir(&(folder->files), folder_name, l_params_length);
	ft_display_result(folder->files, l_params_length);
	if (ft_indexof(g_flags, 'r') >= 0)
		ft_rev_file(&folder->files);


	ft_sort_lexico(&folder->files);

	ft_putstr("total ");
	ft_putstr(ft_itoa(folder->files->size));
	ft_putchar('\n');
	while (folder->files)
	{
		i = 0;
		ft_putstr(folder->files->l[0]);
		ft_putchar(' ');
		while (++i < 6)
		{
			if (ft_strlen(folder->files->l[i]) < l_params_length[i])
			{
				if (i == 2 || i == 3)
				{
					tmp = ft_padding(folder->files->l[i], (l_params_length[i] -
						ft_strlen(folder->files->l[i])) + 1, 'l');
					ft_putstr(tmp);
					ft_putchar(' ');
				}
				else
				{
					tmp = ft_padding(folder->files->l[i], l_params_length[i] -
						ft_strlen(folder->files->l[i]), 'r');
					ft_putstr(tmp);
					ft_putchar(' ');
				}
			}
			else
			{
				ft_putstr(folder->files->l[i]);
				ft_putchar(' ');
			}
			if (i == 2 || i == 3)
				ft_putchar(' ');
		}
		ft_display_color(folder->files);
		ft_putchar('\n');
		ft_putstr(ANSI_COLOR_RESET);
		folder->files = folder->files->next;
	}
	return (0);
}
