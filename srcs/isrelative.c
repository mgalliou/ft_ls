/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isrelative.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 14:38:38 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/05 16:00:58 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int	isrelative(char *filename)
{
	if (!ft_strcmp(filename, ".") || !ft_strcmp(filename, ".."))
		return (1);
	return (0);
}
