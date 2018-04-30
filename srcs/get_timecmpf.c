/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_timecmpf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 14:15:17 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/27 14:23:32 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int		cmpatime(void *a, void *b)
{
	int	diff;

	diff = ((t_file*)b)->stat.st_atime -
			((t_file*)a)->stat.st_atime;
	if (!diff)
	{
		return (((t_file*)b)->stat.st_atime -
				((t_file*)a)->stat.st_atime);
	}
	return (diff);
}

static int		cmpctime(void *a, void *b)
{
	int	diff;

	diff = ((t_file*)b)->stat.st_ctime -
			((t_file*)a)->stat.st_ctime;
	if (!diff)
	{
		return (((t_file*)b)->stat.st_ctime -
				((t_file*)a)->stat.st_ctime);
	}
	return (diff);
}

static int		cmpmtime(void *a, void *b)
{
	int	diff;

	diff = ((t_file*)b)->stat.st_mtime -
			((t_file*)a)->stat.st_mtime;
	if (!diff)
	{
		return (((t_file*)b)->stat.st_mtime -
				((t_file*)a)->stat.st_mtime);
	}
	return (diff);
}

/*static int		cmpbirthtime(void *a, void *b)
{
	int	diff;

	diff = ((t_file*)b)->stat.st_birthtime.tv_sec -
			((t_file*)a)->stat.st_birthtime.tv_sec;
	if (!diff)
	{
		return (((t_file*)b)->stat.st_birthtime.tv_nsec -
				((t_file*)a)->stat.st_birthtime.tv_nsec);
	}
	return (diff);
}*/

void			*get_timecmpf(char *opts)
{
	if (opts['c'])
		return (&cmpctime);
	else if (opts['u'])
		return (&cmpatime);
	else if (opts['U'])
		return (&cmpctime);
	return (&cmpmtime);
}
