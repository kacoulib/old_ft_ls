/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:38:11 by kacoulib          #+#    #+#             */
/*   Updated: 2017/01/18 16:39:45 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

# include "libft/libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h> // to remove

typedef struct		s_file
{
	char			*name;
	char			*path;
	char			*info;
	char			*l[8];
	int				size;
	int				type;
	struct stat		*sb;
	struct s_file	*files;
	struct s_file	*folders;
	struct s_file	*next_folder;
	struct s_file	*parent;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

char *g_flags = "aflRrtu";

int					ft_display_error(char *s, char *type);
int					ft_display_extra_l_first_part(t_file *folder, t_file *file, int l_len[]);
int					ft_display_extra_l_second_part(t_file *file, int l_len[], int i);
int					ft_display_extra_l_third_part(t_file *file, int l_len[], int i);
int					ft_display_result(t_file **folder, t_file *file, int l_len[]);
int					ft_display_color(t_file *file);
int					ft_display_color_extra(t_file *file);
t_file				*ft_init_folder(char *name, t_file *parent, t_file *prev);
char				*ft_padding(char *s, int offset, char direction);
int					ft_parse_dir(t_file *file, int l_len[]);
int					ft_parse_dir_last_part(t_file *file, struct dirent *tmp, int l_len[]);
int					ft_push_folder(t_file *file, t_file *new_file);
int					ft_rev_file(t_file *file);
int					ft_set_acl(t_file *line);
int					ft_set_extra_info(t_file *file, int l_len[]);
int					ft_set_params(char **av);
int					ft_set_permissions(t_file *file, int l_len[]);
int					ft_set_permissions_last_part(t_file *file);
int					ft_set_time(t_file *file);
int					ft_set_user_name(t_file *file, int l_len[]);
int					ft_sort_by_last_modify(t_file **file);
int					ft_sort_lexico(t_file **file);
int					ft_swap_file(t_file **file, t_file *current, t_file *tmp);

# define ANSI_COLOR_BLACK	"\x1b[30m\x1b[42m"
# define ANSI_COLOR_RED		"\x1b[31m"
# define ANSI_COLOR_GREEN	"\x1b[32m"
# define ANSI_COLOR_YELLOW	"\x1b[33m"
# define ANSI_COLOR_BLUE	"\x1b[34m"
# define ANSI_COLOR_MAGENTA	"\x1b[35m"
# define ANSI_COLOR_CYAN	"\x1b[36m"
# define ANSI_COLOR_RESET	"\x1b[0m"

# include "ft_settings.c"
# include "ft_settings_2.c"
# include "ft_displays.c"
# include "ft_displays_2.c"
# include "ft_sorts.c"
#endif
