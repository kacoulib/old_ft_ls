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

char				*ft_padding_left(char *s, int offset)
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
	ft_strcpy(&(tmp)[offset], s);
	return (tmp);
}

t_file				*ft_init_folder(char *name)
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
	file->next = NULL;
	return (file);
}

int					ft_parse_dir(t_file **file, char *name, int l[])
{
	struct dirent	*tmp;
	DIR				*dir;
	t_file			*current;

	if (!(dir = opendir(name)))
	{
		printf(ANSI_COLOR_RED"error openning file %s\n", name);
		return (0);
	}
	name = ft_strjoin(name, ft_strdup("/"));
	while ((tmp = readdir(dir)))
	{
		if ((tmp->d_name[0] != '.' || (ft_indexof(g_flags, 'a') >= 0) ? 1 : 0)) // if hidden file
		{
			if (!(*file) && ((*file = ft_init_folder(tmp->d_name))))
				current = *file;
			else if ((current->next = ft_init_folder(tmp->d_name)))
				current = current->next;
			if (!ft_set_file(current, ft_strjoin(name, tmp->d_name), tmp->d_name, tmp->d_type))
			{
				printf(ANSI_COLOR_YELLOW "-%s\n"ANSI_COLOR_RESET, current->name);
				return (0);
				// return (ft_display_error(name, 0));
			}
			if (tmp->d_type == 4 && ft_indexof(g_flags, 'R') >= 0)
				if (ft_strcmp(tmp->d_name, ".") != 0 && ft_strcmp(tmp->d_name, "..") != 0)
					if (!ft_parse_dir(&(current->files), ft_strjoin(name, tmp->d_name), l))
						printf("____%s\n", current->name);
			// printf("%s \t%s\n", current->path, current->name);

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

	i = 0;
	folder = NULL;
	if ((i = ft_set_params(av)) < 0)
		return (ft_display_error(folder_name, 0));
	folder_name = (av[i]) ? ft_strdup(av[i]) : ft_strdup(".");
	if (!(folder = ft_init_folder(folder_name)))
		return (ft_display_error(folder_name, 0));
	ft_parse_dir(&(folder->files), folder_name, l_params_length);
	ft_display_result(folder->files, l_params_length);
	printf("\n\n");
	if (ft_indexof(g_flags, 'r') >= 0)
		ft_rev_file(&folder->files);
	while (folder->files)
	{
		i = 0;
		printf("%s ", folder->files->l[0]);
		while (++i < 6)
		{
			if (ft_strlen(folder->files->l[i]) < l_params_length[i])
				printf("%s ", ft_padding_left(folder->files->l[i], l_params_length[i] - ft_strlen(folder->files->l[i])));
			else
				printf("%s ", folder->files->l[i]);
		}
		printf("%s\n", folder->files->name);
		folder->files = folder->files->next;
	}
	return (0);
}
