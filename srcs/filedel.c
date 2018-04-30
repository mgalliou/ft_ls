/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 14:43:35 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/26 15:59:11 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		filedel(void *file)
{
	t_file *tmp;

	tmp = file;
	if (file)
	{
		ft_strdel(&tmp->fullname);
		ft_memdel((void*)&tmp);
		file = NULL;
	}
}
