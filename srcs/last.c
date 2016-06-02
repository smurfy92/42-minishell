/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:42:17 by jtranchi          #+#    #+#             */
/*   Updated: 2016/06/01 14:42:19 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void		ft_cd_reset(t_term *term)
{
	char				*buf;

	buf = NULL;
	ft_process_unsetenv(term, "OLDPWD");
	ft_process_setenv(term, "OLDPWD", ft_get_env_by_name(term, "PWD"));
	chdir(term->cmds[1]);
	ft_process_unsetenv(term, "PWD");
	ft_process_setenv(term, "PWD", getwd(buf));
}
