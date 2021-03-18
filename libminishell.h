/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisha <melisha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:08:24 by melisha           #+#    #+#             */
/*   Updated: 2021/03/18 12:53:59 by melisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMINISHELL_H
# define LIBMINISHELL_H
# include <unistd.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include "strminishell.h"
# include "parser/fn_validation_for_argument/validator.h"

void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst,
		void *(*f)(void *), void (*del)(void *));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
void	ft_pwd();
void	unset(t_list *env_list, char *name_varible);
void	add_list_env(t_list *env_list, t_list *export_list, char **envp);
void	output_list(t_list *list);
void	output_export_list(t_list *export);
int		exist_value_env(t_list *list, char *value);
void	export_varible_in_env(t_list *env_list,
	char *name_varible, char *value_varible);
int		get_next_line(char **line, int fd);
void	sorting_export_list(t_list *list);
void	export_varible_in_env(t_list *env_list,
		char *name_varible, char *value_varible);
char	**ft_split(char const *s, char c);
int		fn_space(char *line, int i);
int		fn_pars_line(t_obj *obj);
void	fn_pars_command(t_obj *obj);
int		ft_atoi(const char *str);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
void	*ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	fn_error(char *str);
void	fn_not_an_identifier(t_obj *obj, char *arg);
void	fn_no_such_file(t_obj *obj);
void	fn_not_a_directory(t_obj *obj);
void	fn_numberic_argument_required(t_obj *obj);
void	fn_command_not_found(t_obj *obj);
void	fn_too_many_arguments(t_obj *obj);
char     *fn_circumcision(char *line, t_obj *obj);
void	fn_pars_argument(t_obj *obj);
int		fn_valid_command(t_obj *obj);
void	fn_valid_arg(t_obj *obj);
int		fn_redirect(t_obj *obj);
int		fn_process_for_pipes(t_obj *obj);
char	*fn_search_enviroment(t_obj *obj, char *name);
void	fn_check_environment_variable(t_obj *obj);
int		fn_back_redirect(t_obj *obj);
char	*ft_itoa(int n);
void	s_ctr_c();
void	s_ctr_sl(int sig);
int		fn_space(char *line, int i);
char	*fn_search_enviroment(t_obj *obj, char *name);
int		ft_strcmp(char *s1, char *s2);
char	*fn_circ_for_red(char *line, t_obj *obj);
char	**ft_split_argv(char const *s, char c);
void    free_double_array(char **array);
int		fn_check_pipe(t_obj *obj);
int		ft_putstr(char *line);
int		fn_check_before_redirect(t_obj *obj);
int		pars_line_with_pipes(t_obj *obj);
void	utils_main(t_obj *obj);
#endif
