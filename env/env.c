#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include <string.h>

typedef struct	s_com_flags
{
	int		exi;
	int		cd;
	int		ec;
	int		pw;
	int		exp;
	int		un;
	int		en;
	int		beg;
}				t_com_flags;
typedef struct		s_pars
{
	char			*line;
	char			*command;
	char			*argument;
	int				quotes;
	t_com_flags		flag;
}					t_pars;
typedef struct	s_obj
{
	t_pars		pars;
	t_list		env_list;
	t_list		export_list;
}				t_obj;

void			add_list_env(t_list *env_list, t_list *export_list, char **envp)
{
	int i;
	int j;
	char *key;
	char *value;

	i = 0;
	j = 0;
	while (envp[i])
	{
		ft_lstadd_back(&env_list, ft_lstnew(envp[i]));
		ft_lstadd_back(&export_list, ft_lstnew(envp[i]));
		i++;
	}
}

void			output_list(t_list *list)
{
	t_list *copy;

	copy = list;
	while (copy->next != NULL)
	{
		copy = copy->next;
		printf("%s\n", copy->content);
	}
}

int				exist_value_env(t_list *list, char *value)
{
	t_list *copy;
	int i;
	char *str;
	// int j;
	int len_value;

	copy = list;
	i = 0;
	// j = 0;
	// printf("\n\n\n\n\n\n\n");
	// printf("STR = %s\n", str);
	len_value = ft_strlen(value);
	while (copy->next != NULL)
	{
		copy = copy->next;
		str = (char *)copy->content;
		// printf("STR = %s\n", str);
		while (str[i] != '=' && str[i] && value[i])
		{
			if (str[i] == value[i])
				i++;
			else
				break ;
		}
		if (len_value == i)
			return (1);
		i = 0;
	}
	return (0);
}

void			export_varible_in_env(t_list *env_list,
	char *name_varible, char *value_varible)
{
	int boolean;
	t_list *copy;
	int len_value;
	char *str;
	int i;
	int j;
	int k;
	t_list *copy_before;
	t_list *new_list;
	t_list *copy_after;

	boolean = exist_value_env(env_list, name_varible);
	len_value = ft_strlen(name_varible);
	copy = env_list;
	i = 0;
	j = 0;
	k = 0;
	if (boolean) // меняем значение существуещей переменной
	{
		// printf("\n\n\n\n\n1\n\n\n\n\n");
		while (copy->next != NULL)
		{
			copy = copy->next;
			str = (char *)copy->content;
			// printf("STR = %s\n", str);
			while (str[i] != '=' && str[i] && name_varible[i])
			{
				if (str[i] == name_varible[i])
					i++;
				else
					break ;
			}
			if (len_value == i)
				break ;
			j++;
		}
		copy_before = env_list->next; // копия перед листом который нужно заменить
		copy_after = copy->next; // копия после листа который нужно заменить
		while (k != (j - 1))
		{
			copy_before = copy_before->next;
			k++;
		}
		// printf("\n\n\nbefore_list = %s\n\n\n\n", (char *)copy_before->content);
		// printf("\n\n\nlist = %s\n\n\n\n", (char *)copy->content);
		// printf("\n\n\nafter_list = %s\n\n\n\n", (char *)copy_after->content);
		free(copy);
		char *new_line = ft_strjoin(name_varible, "="); // MALLOC
		new_line = ft_strjoin(new_line, value_varible); // MALLOC
		copy_before->next = ft_lstnew(new_line);
		copy_before->next->next = copy_after;
		// t_list *delete_list = copy_before;
		// printf("\n\n\ndelete_list = %s\n\n\n\n", (char *)delete_list);
		// free(copy);
		// copy_before->next = ft_lstnew(new_line);
		// copy_before->next->next = copy_after;
		// // ft_lstadd_back(&copy_before, ft_lstnew(name_varible));
		// copy_before->next = copy_after;
		// printf("\n\n%s\n", (char *)copy->content);
		// free(copy->content);
	}
	else // добавляем переменную и значение
	{
		char *new_line;

		new_line = ft_strjoin(name_varible, "="); // MALLOC
		new_line = ft_strjoin(new_line, value_varible); // MALLOC
		ft_lstadd_back(&env_list, ft_lstnew(new_line));
		// output_list(env_list);
	}
	// ДОБАВИТЬ В КОНЕЦ env l-value && r-value
	// ft_lstadd_back(*env_list, ft_lstnew());
	// int i;
	// t_list *copy;

	// i = 0;
	// copy = env_list;
	// while (copy->next != NULL)
	// {

	// }
}

void			unset(t_list *env_list, char *name_varible)
{
	t_list *copy;
	t_list *before;
	t_list *after;
	int i;
	int j;
	int k;
	char *str;
	int len_str;
	int boolean; // существует аргумент или нет

	copy = env_list;
	i = 0;
	j = 0;
	k = 0;
	len_str = ft_strlen(name_varible);
	boolean = exist_value_env(env_list, name_varible);
	if (boolean)
	{
		while (copy->next != NULL)
		{
			copy = copy->next;
			str = copy->content;
			while (str[i] == name_varible[i] && str[i] != '\0' && name_varible[i] != '\0')
				i++;
			if (len_str == i && str[i] == '=')
				break ;
			i = 0;
			j++;
		}
		after = copy->next;
		before = env_list->next;
		while (k != (j - 1))
		{
			before = before->next;
			k++;
		}
		free(copy);
		if (before->next != NULL)
			before->next = after;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void			output_export_list(t_list *export)
{
	t_list *copy;
	int i;
	char *str;

	copy = export->next;
	i = 0;
	while (copy != NULL)
	{
		str = (char *)(copy->content);
		ft_putstr_fd("declare -x ", 1);
		while (str[i] != '=' && str[i])
			write(1, &str[i++], 1);
		if (str[i] == '=')
			write(1, &str[i++], 1);
		write(1, "\"", 1);
		while (str[i])
			write(1, &str[i++], 1);
		write(1, "\"", 1);
		// write(1, (char *)(copy->content), ft_strlen((char *)(copy->content)));
		write(1, "\n", 1);
		copy = copy->next;
		i = 0;
	}
}

void			sorting_export_list(t_list *list)
{
	t_list *copy;
	t_list *next;
	char *str1;
	char *str2;
	char *tmp;

	copy = list->next;
	next = list->next->next;
	while (copy->next != NULL)
	{
		while (next->next != NULL)
		{
			str1 = (char *)(copy->content);
			str2 = (char *)(next->content);
			// if (ft_strncmp(str1, str2, ft_strlen(str1)) == 1)
			if (ft_strcmp(str1, str2) > 0)
			{
				tmp = str1;
				// str1 = str2;
				// str2 = tmp;
				copy->content = str2;
				next->content = tmp;
			}
			next = next->next;
		}
		copy = copy->next;
		next = copy;
	}
	output_export_list(list);
}

// список env лежит в obj.env_list
int				main(int argc, char **argv, char **envp)
{
	t_obj obj;
	// ft_lstnew(&obj.env_list);
	add_list_env(&obj.env_list, &obj.export_list, envp); // положить envp в связный список
	// output_list(&obj.env_list); // вывести list_env
	// export_varible_in_env(&obj.env_list, "EGOR", "228");
	// export_varible_in_env(&obj.export_list, "EGOR", "228");
	// export_varible_in_env(&obj.export_list, "a", "123");
	// sorting_export_list(&obj.export_list);
	unset(&obj.env_list, "a");
	unset(&obj.env_list, "ass");
	output_list(&obj.env_list); // вывести list_env
	// unset(&obj.export_list, "EGOR");
	// sorting_export_list(&obj.export_list);
	// printf("\n\n\n\nNEW_ENV!!!\n");
	// output_list(&obj.env_list);
	// // printf("\n\n\n\nDELETE_ENV!!!\n");
	// // unset(&obj.env_list, "TERM");
	// // printf("\n\n\n\nDELETE_ENV!!!\n");
	// unset(&obj.env_list, "EGOR");
	// printf("\n\n\n\nNEW_ENV!!!\n");
	// output_list(&obj.env_list);
	// printf("\n\n\n\nSORT_ENV!!!\n");
	// sorting_export_list(&obj.export_list);
	// printf("\n\n\n\nNEW_ENV!!!\n");
	// output_list(&obj.env_list);
	// output_list(&obj.env_list);
	/*
	* вывод списка
	*/
	// printf("%s\n", (char *)obj.env_list->content);
	// t_list *next;
	// next = &obj.env_list;
	// printf("%s\n", (char *)next);
	// while (next)
	// {
	// 	printf("%s\n", next->content);
	// 	next = next->next;
	// }
	// while (obj.env_list->next)
	// {
	// 	printf("%s\n", (char *)obj.env_list->next);
	// 	obj.env_list = (obj.env_list->next);
	// }
	// int i = 0;
	// int j = 0;
	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }
}
