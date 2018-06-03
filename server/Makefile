##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile for server
##

NAME		:= ../zappy_server
SRC		:= src/main.c \
		   src/communication.c \
		   src/containers/list.c \
		   src/containers/queue.c \
		   src/inventory.c \
		   src/loop.c \
		   src/parse.c \
		   src/player.c \
		   src/space.c \
		   src/team.c \
		   src/events.c

CC		:= gcc
RM		:= rm -f

CFLAGS		:= -Wall -Wextra
CPPFLAGS	:= -Iinclude

$(NAME): $(SRC:src/%.c=obj/%.o)
	$(CC) $(OUTPUT_OPTION) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS)
	-echo -e "\e[1mlinked '$@'\e[0m"

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(OUTPUT_OPTION) -c $(CFLAGS) $(CPPFLAGS) $^
	@-echo "built '$@'"

clean:
	-$(RM) -v $(SRC:src/%.c=obj/%.o)
	-$(RM) -r obj

fclean: clean
	-$(RM) -v $(NAME)

.SILENT: clean fclean $(NAME) obj/%.o

.PHONY: clean fclean
