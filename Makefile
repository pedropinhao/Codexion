NAME := Codexion

COMPILE := cc -Wall -Werror -Wextra -g -I./includes
SRCS := srcs/main.c \
		srcs/parser/parser.c \
		srcs/init/init_config.c \
		srcs/init/init_coders.c \
		srcs/init/init_sim.c \
		srcs/init/init_dongles.c \
		srcs/utils/destroy.c \
		srcs/utils/time.c
OBJS := $(SRCS:.c=.o)
ARGS ?=


all: $(NAME)

$(NAME): $(OBJS)
	$(COMPILE) $(OBJS) -o $(NAME)

%.o: %.c
	$(COMPILE) -c $< -o $@

clean:
	@rm -fr $(OBJS)

fclean: clean
	@rm -fr $(NAME)

debug: re
	gdb $(NAME) $(ARGS)

re: fclean all

run: $(NAME)
	./$(NAME) $(ARGS)

.PHONY: all clean fclean re debug run
