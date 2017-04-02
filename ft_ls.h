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

# include "lib/libft/libft.h"
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
	struct s_file	*parent;
	struct s_file	*errors;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

char *g_flags = "aflRrtu";

int					ft_display_color(t_file *file);
int					ft_display_color_extra(t_file *file);
int					ft_display_folder(t_file *folder, int l_len[]);
int					ft_display_folder_files(t_file *folder, int l_len[]);
int					ft_display_recursive(t_file *file, int l_len[],
	int is_multiple_folder, int is_first);
int					ft_display_result(t_file *file, int l_len[],
	int is_multiple_folder, int i);
t_file				*ft_init_folder(char *name, t_file *parent, t_file *prev);
int					ft_is_file(char *path);
char				*ft_padding(char *s, int offset, char direction);
int					ft_parse_dir(t_file *file, t_file *current, int l_len[], struct dirent *tmp);
int					ft_parse_dir_last_part(t_file *file, struct dirent *tmp,
	int l_len[]);
int					ft_print(char *s1, char *s2, char *s3, char *s4);
int					ft_push_file(t_file *parent, t_file *file);
int					ft_rev_file(t_file **file);
int					ft_set_acl(t_file *line);
int					ft_set_error(t_file *file, char *s, char *type);
int					ft_set_extra_info(t_file *file, int l_len[]);
int					ft_set_params(t_file *file, char **av, int i);
int					ft_set_permissions(t_file *file, int l_len[],
	struct stat *sb);
int					ft_set_time(t_file *file);
int					ft_set_user_name(t_file *file, int l_len[]);
int					ft_sort_settings(t_file **file);
int					ft_sort_by_last_modify(t_file **file);
int					ft_sort_lexico(t_file **file);
int					ft_swap_file(t_file **file, t_file *current,
	t_file *tmp);

# define setColor 0
# define ANSI_COLOR_BLACK	"\x1B[30m\x1B[42m"
# define ANSI_COLOR_RED		"\x1B[31m"
# define ANSI_COLOR_GREEN	"\x1B[32m"
# define ANSI_COLOR_YELLOW	"\x1B[33m"
# define ANSI_COLOR_BLUE	"\x1B[34m"
# define ANSI_COLOR_MAGENTA	"\x1B[35m"
# define ANSI_COLOR_CYAN	"\x1B[36m"
# define ANSI_COLOR_RESET	"\x1B[0m"

# include "src/settings/ft_settings.c"
# include "src/settings/ft_settings_2.c"
# include "src/displays/ft_displays.c"
# include "src/displays/ft_displays_2.c"
# include "src/sortings/ft_sorts.c"
# include "src/sortings/ft_sorts2.c"
#endif
