_RED	=	\033[31m
_GREAN	=	\033[32m
_YELLOW	=	\033[33m
_BLUE	=	\033[34m
_END	=	\033[0m

NAME1	=	server
NAME2	=	client

SRCS_SERVER	= server.c util.c

SRCS_CLIENT	= client.c util.c


OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

CC	= gcc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME1) $(NAME2)


$(NAME1) : $(OBJS_SERVER)
	@$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(NAME1) 
	@echo "\nFINISH Compiling $(NAME1)!"
	@echo "$(_YELLOW)Try \"./$(NAME1) first$(_END)"

$(NAME2) : $(OBJS_CLIENT)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(NAME2) 
	@echo "\nFINISH Compiling $(NAME2)!"
	@echo "$(_YELLOW)Try \"./$(NAME2) first$(_END)"

clean:
	@echo "$(_BLUE)Removing object files....$(END)"
	@rm -rf $(OBJS_CLIENT) $(OBJS_SERVER)

fclean:
	@echo "$(_RED)Removing object files and program....$(_END)"
	@rm -rf $(OBJS_CLIENT) $(OBJS_SERVER) $(NAME1) $(NAME2)

re: fclean all

%.o: %.c
	@$(CC) -c $(CFLAGS) -o $@ $<
	@printf "$(_GREAN)>$(_END)"

PHONY: all clean fclean re
