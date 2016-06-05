/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/08 12:46:12 by jtranchi          #+#    #+#             */
/*   Updated: 2016/04/08 12:46:13 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void		ft_env_i(t_term *term)
{
	int y;
	int i;

	y = -1;
	while (term->env[++y])
		term->env[y] = NULL;
	i = -1;
	while (term->cmds[++i])
	{
		if (ft_strchr(term->cmds[i], '='))
		{
			y = 0;
			while (term->env[y])
				y++;
			term->env[y] = ft_strdup(term->cmds[i]);
		}
	}
}

char		*ft_tab_replace(char **str)
{
	int i;

	i = -1;
	while (((*str)[0] == '\t' || (*str)[0] == ' ') && (*str)[1])
		(*str) = &(*str)[1];
	while ((*str)[++i])
		if ((*str)[i] == '\t' && (*str)[i + 1])
			(*str)[i] = ' ';
		else if ((*str)[i] == '\t' && !(*str)[i + 1])
			(*str)[i] = '\0';
	return (*str);
}

void		ft_cd_error(char *cmd)
{
	ft_putendl(ft_strjoin("cd: no such file or directory: ", cmd));
}

void		ft_exit(void)
{
	write(1, "\n", 1);
	exit(0);
}

void		ft_cd_home(t_term *term)
{
	char				*buf;

	buf = NULL;
	if (!ft_get_val_exists(term, "HOME"))
		return (ft_putendl("NO HOME"));
	ft_process_unsetenv(term, "OLDPWD");
	ft_process_setenv(term, "OLDPWD", ft_get_env_by_name(term, "PWD"));
	chdir(ft_get_val(term, "HOME"));
	ft_process_unsetenv(term, "PWD");
	ft_process_setenv(term, "PWD", getwd(buf));
}
