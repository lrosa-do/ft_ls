NAME = ft_ls

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
SANITIZE = -fsanitize=address,undefined -fno-omit-frame-pointer

SRCDIR = src
OBJDIR = obj

# TEST SRCS = $(SRCDIR)/main.c $(SRCDIR)/utils.c $(SRCDIR)/path.c $(SRCDIR)/info.c $(SRCDIR)/vector.c
SRCS = $(SRCDIR)/ft_ls.c $(SRCDIR)/utils.c $(SRCDIR)/path.c $(SRCDIR)/info.c $(SRCDIR)/vector.c
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(SANITIZE) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
