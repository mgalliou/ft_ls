/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xattr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 12:10:45 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/25 16:55:07 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <sys/xattr.h>
#include <sys/acl.h>

static int	get_xattrpad(char *path, char *buf, int size)
{
	int	tmp;
	int	pad;
	int i;

	i = 0;
	pad = 0;
	while (i < size - 1)
	{
		tmp = ft_nbrlen(getxattr(path, &buf[i], NULL, size, 0, 0));
		if (pad < tmp)
			pad = tmp;
		i += ft_strlen(&buf[i]) + 1;
	}
	return (pad);
}

void		print_xattr(t_file *file, char *opts)
{
	char	*buf;
	int		bufsize;
	int		size;
	int		pad;
	int		i;

	if (file->hasxattr)
	{
		bufsize = listxattr(file->fullname, NULL, 0, 0);
		buf = ft_strnew(bufsize);
		size = listxattr(file->fullname, buf, bufsize, 0);
		pad = get_xattrpad(file->fullname, buf, size);
		i = 0;
		while (i < size - 1)
		{
			ft_printf("\t%s\t%*d\n", &buf[i],
					pad, getxattr(file->fullname, &buf[i], NULL, size, 0, 0));
			i += ft_strlen(&buf[i]) + 1;
		}
		ft_strdel(&buf);
	}
}
