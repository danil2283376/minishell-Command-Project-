#include "../libminishell.h"

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
	char *leaks;
	t_list *current;

	boolean = exist_value_env(env_list, name_varible);
	len_value = ft_strlen(name_varible);
	copy = env_list;
	i = 0;
	j = 0;
	k = 0;
	char *new_line;
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
			{
				current = copy;
				break ;
			}
			j++;
		}
		copy_before = env_list->next;
		copy_after = copy->next;
		while (k != (j - 1))
		{
			copy_before = copy_before->next;
			k++;
		}
		free(current->content);
		free(copy);
		new_line = ft_strjoin(name_varible, "=");
		leaks = new_line;
		new_line = ft_strjoin(new_line, value_varible); // MALLOC
		free(leaks);
		copy_before->next = ft_lstnew(new_line);
		copy_before->next->next = copy_after;
	}
	else
	{
		char *leaks1;
		if (value_varible[0] == '\0')
		{
			new_line = ft_strdup(name_varible);
			ft_lstadd_back(&env_list, ft_lstnew(new_line));
		}
		else
		{
			new_line = ft_strjoin(name_varible, "=");
			if (*value_varible != '\n')
			{
				leaks = new_line;
				new_line = ft_strjoin(new_line, value_varible);
				free(leaks);
			}
			ft_lstadd_back(&env_list, ft_lstnew(new_line));
		}
	}
}
