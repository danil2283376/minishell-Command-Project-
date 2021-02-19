#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_com_flags
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
}				t_obj;

/*
* Возвращает путь папки в которой находишься
*/

char	*ft_pwd(t_obj *obj)
{
	char *path;
	char *buf;
	long size;
	char *ptr;

	size = pathconf(".", _PC_PATH_MAX);
	if (!(buf = malloc(size)))
		return (NULL);
	ptr = getcwd(buf, size);
	return (ptr);
}

int main()
{
	t_obj obj;
	char *path = ft_pwd(&obj);
	printf("%s\n", path);
}
