/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 13:37:45 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/27 14:23:09 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <libft.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>

# define OPTIONS "ABCFGHLOPRSTUW@abcdefghiklmnopqrstuwx1"

typedef struct		s_pad
{
	int				block;
	int				link;
	int				usr;
	int				grp;
	int				size;
}					t_pad;

/*
**enum				e_filetype
**{
**    di, bl
**};
*/

typedef struct		s_file
{
	char			*name;
	char			*fullname;
	struct stat		stat;
	struct passwd	*pwd;
	struct group	*grp;
	t_pad			*pad;
	int				hasxattr;
	int				hasacl;
}					t_file;

char				*get_options(char **av, int *i);
void				*get_cmpf(char *opts);
void				*get_timecmpf(char *opts);
char				*create_path(char *dir, char *file);
t_file				*filenew(char *dir, char *filename, char *opts, t_pad *pad);
void				filedel(void *file);
t_rb_node			*get_files(char *dir, char *opts,
							int (*cmpfct)(void *a, void *b));
void				extract_files(t_rb_node **files, t_rb_node *args,
							char *opts);

/*
**	PRINTING
*/

void				print_files(t_rb_node *files, char *opts);
t_pad				*get_paddings(t_file *files, t_pad *pad, char *opts);
void				print_incolumn(t_rb_node *files, char *opts);
void				print_long_format(t_file *file, char *opts);
char				*get_mode(mode_t mode, char *str);
char				*get_timestring(t_file *file, char *opts);
void				print_filename(t_file *file, char *opts);
void				print_xattr(t_file *file, char *opts);
void				print_acl(t_file *file, char *opts);

/*
** TOOLKIT
*/

int					isrelative(char *filename);

#endif
