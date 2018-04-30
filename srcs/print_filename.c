/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 13:16:38 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/25 16:56:23 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static void			print_link(char *path)
{
	char	*buf;
	int		bufsize;

	bufsize = 64;
	buf = ft_strnew(bufsize);
	while ((readlink(path, buf, bufsize) == bufsize))
	{
		ft_strdel(&buf);
		bufsize *= 2;
		buf = ft_strnew(bufsize);
	}
	ft_printf(" -> %s", buf);
	ft_strdel(&buf);
}

static const char	*get_indicator(t_file *file, char *opts)
{
	if (opts['p'] && S_ISDIR(file->stat.st_mode))
		return ("/");
	else if (opts['F'])
	{
		if (S_ISDIR(file->stat.st_mode))
			return ("/");
		else if (S_ISSOCK(file->stat.st_mode))
			return ("=");
		else if (S_ISLNK(file->stat.st_mode))
			return ("@");
		else if (S_ISFIFO(file->stat.st_mode))
			return ("|");
		else if (S_IXUSR & file->stat.st_mode)
			return ("*");
		else if (S_ISWHT(file->stat.st_mode))
			return ("%");
	}
	return ("");
}

static const char	*get_colorcode(t_file *file, char *opts)
{
	if (opts['G'])
	{
		if (S_ISBLK(file->stat.st_mode))
			return ("\e[38;2;175;129;255m\e[48;2;102;207;239m");
		else if (S_ISCHR(file->stat.st_mode))
			return ("\e[38;2;175;129;255m\e[48;2;253;151;31m");
		else if (S_ISDIR(file->stat.st_mode))
			return ("\e[38;2;102;207;239m");
		else if (S_ISSOCK(file->stat.st_mode))
			return ("\e[38;5;45m");
		else if (S_ISLNK(file->stat.st_mode))
			return ("\e[38;2;249;42;114m");
		else if (S_ISFIFO(file->stat.st_mode))
			return ("\e[38;2;253;151;31m");
		else if (S_IXUSR & file->stat.st_mode)
			return ("\e[38;2;166;226;46m");
	}
	return ("");
}

void				print_filename(t_file *file, char *opts)
{
	ft_printf("%s%s%s%s", get_colorcode(file, opts), file->name,
			(opts['G'] ? "\e[m" : ""),
			get_indicator(file, opts));
	if (opts['l'] && S_ISLNK(file->stat.st_mode))
		print_link(file->fullname);
}
