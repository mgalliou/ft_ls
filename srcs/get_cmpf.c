/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_compf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 15:55:35 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/27 14:54:37 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int		cmpascii(void *a, void *b)
{
	return (ft_strcmp(((t_file*)a)->name, ((t_file*)b)->name));
}

static int		cmpsize(void *a, void *b)
{
	if (S_ISBLK(((t_file*)b)->stat.st_mode) ||
			S_ISBLK(((t_file*)b)->stat.st_mode) ||
			S_ISCHR(((t_file*)a)->stat.st_mode) ||
			S_ISBLK(((t_file*)a)->stat.st_mode))
		return (ft_strcmp(((t_file*)a)->name, ((t_file*)b)->name));
	return (((t_file*)b)->stat.st_size - ((t_file*)a)->stat.st_size);
}

void			*get_cmpf(char *opts)
{
	if (opts['S'])
		return (&cmpsize);
	else if (opts['t'])
		return (get_timecmpf(opts));
	if (opts['f'])
		return (NULL);
	return (&cmpascii);
}
