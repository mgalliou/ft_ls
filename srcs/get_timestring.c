/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_timestring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 17:33:02 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/27 14:20:34 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static time_t	choose_time(struct stat stat, char *opts)
{
	if (opts['t'])
	{
		if (opts['c'])
			return (stat.st_ctime);
		else if (opts['u'])
			return (stat.st_atime);
//		else if (opts['U'])
//			return (stat.st_birthtime);
	}
	return (stat.st_mtime);
}

char			*get_timestring(t_file *file, char *opts)
{
	char		*tmp;
	time_t		date;

	date = choose_time(file->stat, opts);
	tmp = ctime(&date);
	if (opts['T'])
		tmp[24] = '\0';
	else
	{
		if ((time(NULL) - date) > 15552000)
		{
			tmp[11] = ' ';
			ft_strncpy(&tmp[12], &tmp[20], 4);
		}
		tmp[16] = '\0';
	}
	return (&tmp[4]);
}
