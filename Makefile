_RED	:=	\033[31m
_GREAN	:=	\033[32m
_YELLOW	:=	\033[33m
_BLUE	:=	\033[34m
_END	:=	\033[0m

NAME	:=	server
NAME2	:=	client

SRCS_SERVER	:= server.c util.c
SRCS_CLIENT	:= client.c util.c

SRCS_SERVER_B	:= server_bonus.c util_bonus.c
SRCS_CLIENT_B	:= client_bonus.c util_bonus.c

OBJS_SERVER := $(SRCS_SERVER:%.c=%.o)
OBJS_CLIENT := $(SRCS_CLIENT:%.c=%.o)

#BONUS = "1"

ifeq ($(BONUS), "1")
SRCS_SERVER	:= $(SRCS_SERVER_B)
SRCS_CLIENT	:= $(SRCS_CLIENT_B)
endif

OBJS_CLIENT_B = $(SRCS_CLIENT_B:%.c=%.o)
OBJS_SERVER_B = $(SRCS_SERVER_B:%.c=%.o)

CC	:= gcc

CFLAGS := -Wall -Werror -Wextra

all: $(NAME) $(NAME2)


$(NAME) : $(OBJS_SERVER)
	@$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(NAME) 
	@echo "\nFINISH Compiling $(NAME)!"
	@echo "$(_YELLOW)Try \"./$(NAME) first$(_END)"

$(NAME2) : $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(NAME2) 
	@echo "\nFINISH Compiling $(NAME2)!"
	@echo "$(_YELLOW)Try \"./$(NAME2) first$(_END)"

clean:
	@echo "$(_BLUE)Removing object files....$(_END)"
	rm -rf $(OBJS_CLIENT) $(OBJS_SERVER)
	rm -rf $(OBJS_CLIENT_B) $(OBJS_SERVER_B)

fclean:
	@echo "$(_RED)Removing object files and program....$(_END)"
	rm -rf $(OBJS_CLIENT) $(OBJS_SERVER)
	rm -rf $(OBJS_CLIENT_B) $(OBJS_SERVER_B)
	rm -rf $(NAME) $(NAME2)

re: fclean all

bonus:
	$(MAKE)
	#$(eval $(BONUS) = "1")$(MAKE)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
	@printf "$(_GREAN)>$(_END)"

PHONY: all clean fclean re bonus
