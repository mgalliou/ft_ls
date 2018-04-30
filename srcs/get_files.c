/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 13:55:27 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/26 16:16:41 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <dirent.h>
#include <sys/errno.h>
#include <string.h>

t_rb_node			*get_files(char *dir, char *opts,
							int (*cmpf)(void *a, void *b))
{
	t_rb_node		*files;
	DIR				*dirp;
	struct dirent	*entry;
	t_pad			*pad;

	files = NULL;
	if (!(pad = ft_memalloc(sizeof(t_pad))))
		exit(EXIT_FAILURE);
	if ((dirp = opendir(dir)))
	{
		while ((entry = readdir(dirp)))
		{
			if (entry->d_name[0] != '.' || opts['a'] ||
					((opts['A']) && !isrelative(entry->d_name)))
				rb_insert(&files,
						filenew(dir, entry->d_name, opts, pad), cmpf);
		}
		closedir(dirp);
	}
	else
		ft_printf("ls: %s: %s\n", dir, strerror(errno));
	if (!files && pad)
		ft_memdel((void*)&pad);
	return (files);
}
