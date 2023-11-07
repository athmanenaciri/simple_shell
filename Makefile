CC = cc

CFLAGS += -Wall -Werror -Wextra
LDFLAGS += -lreadline

DBUILD = build

HEADER_FILES = $(addprefix inc/, minishell.h list.h exec.h)

FILES = main check_errors heredoc exec expand_variables lexer/lexer list/ft_lst_new list/ft_lst_new_ev \
		list/ft_lstadd_back list/ft_lstadd_back_ev list/ft_lstadd_back_cmd \
		list/ft_lstsize str/ft_strndup str/ft_strlen str/ft_strncmp \
		str/ft_strnjoin str/ft_strlcpy str/ft_strchar tokens/dolar \
		tokens/quotes tokens/string utils/skip utils/till utils/is_redirection \
		utils/ft_isalnum utils/ft_isdigit utils/ft_isalpha \
		utils/ft_join var/var_len var/get_var var/get_var_extra \
		exec/builtins exec/execution exec/execution_extra exec/ft_dup exec/utils \
		exec/builtins/execute_cd list/ft_destroy signals exec/execution_extramax exec/builtins_extra \

OBJS = $(addprefix $(DBUILD)/, $(FILES:=.o))

NAME = minishell

all: $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(DBUILD)/%.o: src/%.c $(HEADER_FILES)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I ./inc

clean:
	rm -rf $(DBUILD)

fclean: clean
	rm -f $(NAME) 

re: fclean all
