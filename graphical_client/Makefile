##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile for zappy project
##

CC		=		g++

CFLAGS		+=		-W -Wall -Wextra -g3

CFLAGS		+=		-I./include

CFLAGS		+=		$(DEBUG)

LDFLAGS		+=

NAME		=		../zappy_graphical

SRCDIR		=		source

SRCS		=		$(addprefix $(SRCDIR)/,	
				main.cpp)

OBJDIR		=		build

OBJS		=		$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o,  $(SRCS))

all:		$(NAME)
		@echo "Done compiling $(NAME)"

$(NAME):	buildrepo $(OBJS)
		@echo "Linking $(NAME)"
		@$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
		@echo "->" $<
		@$(CC) -c $< -o $@ $(CFLAGS)

tests_run:
		@[ -d tests ] && make --no-print-directory -C tests || echo -n

buildrepo:
		@$(call build-repo)

clean:
		@echo "Cleaning object files"
		@rm -rf $(OBJDIR)


fclean:		clean
		@echo "Cleaning binary"
		@rm -f $(NAME)

re:		fclean all

define build-repo
	for dir in $(dir $(OBJS));	\
	do				\
		mkdir -p $$dir;		\
	done
endef

.PHONY: all tests_run buildrepo clean fclean re
