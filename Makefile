O_DIR	=	./objs
C_SRCS	=	client.c
C_NAME	=	client
C_OBJS	=	${C_SRCS:%.c=$(O_DIR)/%.o}

S_SRCS	=	server.c
S_NAME	=	server
S_OBJS	=	${S_SRCS:%.c=$(O_DIR)/%.o}

U_SRCS	=	utils.c
U_OBJS	=	${U_SRCS:%.c=$(O_DIR)/%.o}

CFLAGS	=	-Wall -Wextra -Werror
CC		=	cc
RM		=	rm -f

all: $(C_NAME) $(S_NAME)
	@printf "all: Done\n"

$(O_DIR)/%.o: %.c
	@printf "1. Compiling objects\r"
	@mkdir -p $(O_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(C_NAME):	$(C_OBJS) $(U_SRCS)
	@printf "\n2. Compiling Client    \n"
	@$(CC) $(CFLAGS) -o $(C_NAME) $(C_OBJS) $(U_SRCS)

$(S_NAME):	$(S_OBJS) $(U_SRCS)
	@printf "3. Compiling Server    \n"
	@$(CC) $(CFLAGS) -o $(S_NAME) $(S_OBJS) $(U_SRCS)

clean:
	@$(RM) -rf $(O_DIR)

fclean:		clean
	@$(RM) $(C_NAME)
	@$(RM) $(S_NAME)

re:			fclean all

.PHONY:		re clean fclean all
