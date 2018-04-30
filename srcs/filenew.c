/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filenew.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:01:42 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/27 16:43:13 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <sys/errno.h>
#include <string.h>

t_file		*filenew(char *dir, char *filename, char *opts, t_pad *pad)
{
	t_file	*new;
	int		i;
	int		(*statf)(const char *path, struct stat *buf);

	if (!(new = ft_memalloc(sizeof(t_file))))
		exit(EXIT_FAILURE);
	if (!(new->fullname = create_path(dir, filename)))
		exit(EXIT_FAILURE);
	i = (dir ? ft_strlen(dir) + 1 : 0);
	new->name = &new->fullname[i];
	new->pad = pad;
	statf = (opts['L'] ? &stat : &lstat);
	if (statf(new->fullname, &new->stat))
	{
		ft_printf("ls: %s: %s\n", new->name, strerror(errno));
		filedel(new);
		return (NULL);
	}
	if (opts['l'])
		new->pad = get_paddings(new, pad, opts);
	return (new);
}
