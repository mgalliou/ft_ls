/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 10:21:23 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/27 16:09:26 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	extract(t_rb_node **files, t_rb_node *args, t_pad *pad,
					char *opts)
{
	if (args)
	{
		extract(files, args->left, pad, opts);
		if (!S_ISDIR(((t_file*)args->item)->stat.st_mode))
		{
			rb_insert(files, args->item, NULL);
			if (opts['i'])
			{
				pad = get_paddings(((t_file*)args->item), pad, opts);
				((t_file*)args->item)->pad = pad;
			}
		}
		extract(files, args->right, pad, opts);
	}
}

void		extract_files(t_rb_node **files, t_rb_node *args, char *opts)
{
	t_pad	*pad;

	ft_memdel((void*)&((t_file*)args->item)->pad);
	if (!(pad = ft_memalloc(sizeof(t_pad))))
		exit(EXIT_FAILURE);
	extract(files, args, pad, opts);
	if (!*files)
		ft_memdel((void*)&pad);
}
