C_SRCS	=	client.c
C_NAME	=	client
C_OBJS	=	${C_SRCS:%.c=%.o}

S_SRCS	=	server.c
S_NAME	=	server
S_OBJS	=	${S_SRCS:%.c=%.o}

U_SRCS	=	utils.c
U_OBJS	=	${U_SRCS:%.c=%.o}

CFLAGS	=	-Wall -Wextra -Werror
CC		=	cc
RM		=	rm -f

all: $(C_NAME) $(S_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(C_NAME):	$(C_OBJS) $(U_SRCS)
	$(CC) $(CFLAGS) -o $(C_NAME) $(C_OBJS) $(U_SRCS)

$(S_NAME):	$(S_OBJS) $(U_SRCS)
	$(CC) $(CFLAGS) -o $(S_NAME) $(S_OBJS) $(U_SRCS)

clean:
	$(RM) $(C_OBJS)
	$(RM) $(S_OBJS)

fclean:		clean
	$(RM) $(C_NAME)
	$(RM) $(S_NAME)

re:			fclean all

.PHONY:		re clean fclean all
