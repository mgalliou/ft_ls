/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paddings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 15:25:53 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/27 17:39:17 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_pad	*get_paddings(t_file *file, t_pad *pad, char *opts)
{
	int	tmp;

	if (opts['s'])
	{
		tmp = ft_nbrlen(file->stat.st_blocks);
		pad->block = (pad->block < tmp ? tmp : pad->block);
	}
	tmp = ft_nbrlen(file->stat.st_nlink);
	pad->link = (pad->link < ++tmp ? tmp : pad->link);
	file->pwd = getpwuid(file->stat.st_uid);
	tmp = (((file->pwd->pw_name && !opts['n']) ?
			ft_strlen(file->pwd->pw_name) : ft_nbrlen(file->stat.st_uid))) + 1;
	pad->usr = (pad->usr < ++tmp ? tmp : pad->usr);
	if (!opts['o'])
	{
		file->grp = getgrgid(file->stat.st_gid);
		tmp = ((file->grp->gr_name && !opts['n']) ?
			ft_strlen(file->grp->gr_name) : ft_nbrlen(file->stat.st_gid)) + 1;
		pad->grp = (pad->grp < ++tmp ? tmp : pad->grp);
	}
	tmp = (S_ISBLK(file->stat.st_mode) || S_ISCHR(file->stat.st_mode) ?
			8 : ft_nbrlen(file->stat.st_size));
	pad->size = (pad->size < tmp ? tmp : pad->size);
	return (pad);
}
