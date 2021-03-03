#include "../libminishell.h"

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
		printf("%s\n", copy->content);/*!PRINTF*/
	}
}

int				exist_value_env(t_list *list, char *value)
{
	t_list *copy;
	int i;
	char *str;
 
	int len_value;

	copy = list;
	i = 0;
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
	if (boolean)
	{
		while (copy->next != NULL)
		{
			copy = copy->next;
			str = (char *)copy->content;
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
		copy_before = env_list->next;
		copy_after = copy->next;
		while (k != (j - 1))
		{
			copy_before = copy_before->next;
			k++;
		}
		free(copy);
		char *new_line = ft_strjoin(name_varible, "="); // MALLOC
		new_line = ft_strjoin(new_line, value_varible); // MALLOC
		copy_before->next = ft_lstnew(new_line);
		copy_before->next->next = copy_after;
	}
	else // добавляем переменную и значение
	{
		char *new_line;
		if (value_varible[0] == '\0')
		{
			new_line = ft_strdup(name_varible);
			ft_lstadd_back(&env_list, ft_lstnew(new_line));
		}
		else
		{
			new_line = ft_strjoin(name_varible, "="); // MALLOC
			new_line = ft_strjoin(new_line, value_varible); // MALLOC
			ft_lstadd_back(&env_list, ft_lstnew(new_line));
		}
	}
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

int		ft_strcmp(char *s1, char *s2)
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
	int	quite;
	char *str;

	copy = export->next;
	i = 0;
	quite = 0;
	while (copy != NULL)
	{
		str = (char *)(copy->content);
		write(1, "declare -x ", 11);
		while (str[i] != '=' && str[i])
			write(1, &str[i++], 1);
		if (str[i] == '=')
		{
			write(1, &str[i++], 1);
			write(1, "\"", 1);
		}
		else
			quite = 1;
		while (str[i])
			write(1, &str[i++], 1);
		if (quite == 0)
			write(1, "\"", 1);
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
			if (ft_strcmp(str1, str2) > 0)
			{
				tmp = str1;
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