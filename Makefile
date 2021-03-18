NAME = minishell

SRC =	fn_check_before_redirect.c fn_check_pipe.c fn_space.c fn_strcmp.c ft_atoi.c \
		ft_bzero.c ft_calloc.c ft_itoa.c ft_putstr.c ft_split.c ft_strdup.c ft_strjoin.c \
		ft_strlen.c ft_strtrim.c ft_substr.c get_next_line.c main.c pars_line_with_pipe.c utils_main.c \
		logic/unset.c logic/pwd.c logic/process_for_pipes.c logic/proc_for_pipe_utils_second.c logic/proc_for_pipe_utils_first.c \
		logic/proc_for_pipe_utils_fird.c logic/output_export.c logic/output_env.c logic/env.c logic/env_utils.c logic/add_lists.c \
		logic/liblist/ft_lstadd_back.c logic/liblist/ft_lstadd_front.c logic/liblist/ft_lstclear.c logic/liblist/ft_lstdelone.c \
		logic/liblist/ft_lstiter.c logic/liblist/ft_lstlast.c logic/liblist/ft_lstmap.c logic/liblist/ft_lstnew.c logic/liblist/ft_lstsize.c \
		logic/liblist/ft_strncmp.c parser/valid_command.c parser/valid_arg.c parser/utils_envir_var.c parser/parser.c parser/pars_command.c \
		parser/pars_argument.c parser/pars_argument_utils.c parser/fn_redirect.c parser/fn_error_processing.c \
		parser/fn_error_processing_utils.c parser/fn_circumcision.c parser/fn_circumcision_utils.c parser/fn_back_redirect.c \
		parser/fn_back_redirect_utils.c parser/error.c parser/error_no_file_or_dir.c parser/environment_variable.c \
		parser/fn_validation_for_argument/fn_valid_cd.c \
		parser/fn_validation_for_argument/fn_valid_ec.c \
		parser/fn_validation_for_argument/fn_valid_en.c \
		parser/fn_validation_for_argument/fn_valid_exi.c \
		parser/fn_validation_for_argument/fn_valid_exp_utils.c \
		parser/fn_validation_for_argument/fn_valid_exp.c \
		parser/fn_validation_for_argument/fn_valid_pw.c \
		parser/fn_validation_for_argument/fn_valid_un.c

HEAD = libminishell.h strminishell.h parser/fn_validation_for_argument/validator.h

all : $(NAME)

$(NAME): $(SRC) $(HEAD)
	gcc -Wall -Werror -Wextra $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean : clean

re: fclean all

.PHONY: all bonus clean fclean re