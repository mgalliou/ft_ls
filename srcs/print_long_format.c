/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 15:00:12 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/27 17:55:53 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <sys/xattr.h>
#include <sys/acl.h>

static char	*get_usr(t_file *file, char *usr, char *opts)
{
	char *tmp;

	if (opts['n'] || !file->pwd->pw_name)
	{
		tmp = ft_itoa(file->stat.st_uid);
		ft_strcpy(usr, tmp);
		ft_strdel(&tmp);
		return (usr);
	}
	else
		return (file->pwd->pw_name);
}

static char	*get_grp(t_file *file, char *grp, char *opts)
{
	char *tmp;

	if (!opts['o'])
	{
		if (opts['n'] || !file->grp->gr_name)
		{
			tmp = ft_itoa(file->stat.st_gid);
			ft_strcpy(grp, tmp);
			ft_strdel(&tmp);
			return (grp);
		}
		else
			return (file->grp->gr_name);
	}
	return ("");
}

static char	get_attr(t_file *file)
{
	acl_t	acl;

	file->hasxattr = 0;
	file->hasacl = 0;
	if (listxattr(file->fullname, NULL, 0, 0) > 0)
	{
		file->hasxattr = 1;
		return ('@');
	}
	if ((acl = acl_get_file(file->fullname, ACL_TYPE_EXTENDED)))
	{
		acl_free((void*)acl);
		file->hasacl = 1;
		return ('+');
	}
	return (' ');
}

void		print_long_format(t_file *file, char *opts)
{
	char	mode[11];
	char	usr[file->pad->usr];
	char	grp[file->pad->grp];

	if (opts['i'])
		ft_printf("%7u ", file->stat.st_ino);
	if (opts['s'])
		ft_printf("%*ju ", file->pad->block, file->stat.st_blocks);
	ft_printf("%s%c%*u %-*s%-*s",
			get_mode(file->stat.st_mode, mode), get_attr(file),
			file->pad->link, file->stat.st_nlink,
			file->pad->usr, get_usr(file, usr, opts),
			file->pad->grp, get_grp(file, grp, opts));
	if (S_ISBLK(file->stat.st_mode) || S_ISCHR(file->stat.st_mode))
		ft_printf("%*u,%*u %s ", 3, major(file->stat.st_rdev),
				4, minor(file->stat.st_rdev), get_timestring(file, opts));
	else
		ft_printf("%*u %s ", file->pad->size, file->stat.st_size,
				get_timestring(file, opts));
}
