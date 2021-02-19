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
* Принимает номер ошибки, пока не знаю как это обработать,
* и куда его записать
*/

void	ft_exit(t_obj *obj, char *error)
{
	write(1, "exit\n", 5);
	exit(1);
}
