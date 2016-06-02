/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/28 21:29:28 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/28 21:29:55 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H
# include "../libft/includes/libft.h"
# include <signal.h>
# include <sys/stat.h>
# include <stdio.h>
# include <termios.h>

typedef	struct			s_term
{
	char				*path;
	pid_t				father;
	struct s_env		*lst;
	int					i;
	char				*u;
	char				**env;
	char				**cmds;
	char				**cmdsplit;
}						t_term;

typedef	struct			s_u
{
	char				*var;
	struct s_env		*next;
}						t_u;

typedef	struct			s_env
{
	char				*var;
	char				*val;
	struct s_env		*next;
}						t_env;

int						ft_check_in_path(t_term *term);
int						ft_get_val_exists(t_term *term, char *str);
int						ft_check_in_env(t_term *term, char *cmd);
void					ft_exit(void);
void					ft_refresh_env(t_term *term);
void					ft_cd_reset(t_term *term);
void					ft_cd_error(char *cmd);
void					ft_cd_home(t_term *term);
void					ft_display_i(t_term *term);
void					ft_newenv_display(t_term *term);
void					ft_display_env(t_term *term);
void					ft_check_env(t_term *term);
void					ft_check_cmds(t_term *term);
void					ft_env_i(t_term *term);
void					ft_permission_denied(char *str);
void					ft_env_options(t_term *term);
void					ft_display_env(t_term *term);
void					ft_prompt(int nb);
void					ft_create_process(t_term *term);
void					ft_check_env(t_term *term);
void					ft_process_unsetenv(t_term *term, char *s1);
void					ft_process_setenv(t_term *term, char *s1, char *s2);
char					*ft_get_env_by_name(t_term *term, char *name);
char					*ft_get_val(t_term *term, char *str);
char					*ft_tab_replace(char **str);
t_env					*ft_parse_env(char **env);
t_env					*ft_add_lst(t_env *tmp, t_env *lst);
t_env					*ft_create_lst(char *str);
t_term					*ft_set_term(char **env, t_env *lst);

#endif
