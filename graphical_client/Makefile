##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile for zappy project
##

CXX		=		g++

<<<<<<< HEAD
CXXFLAGS	+=		-W -Wall -Wextra -g3 -std=c++11
=======
CXXFLAGS	+=		-W -Wall -Wextra -g3
>>>>>>> 3d9bf1fdfb2af18b87c361c74c6081c20522588f

CPPFLAGS	+=		-Iinclude

CXXFLAGS	+=		$(DEBUG)

LDFLAGS		+=		 -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio

NAME		=		../zappy_graphical

SRCDIR		=		source

SRCS		=		$(addprefix $(SRCDIR)/, \
				IEntity.cpp \
				Incantation.cpp \
				Map.cpp \
				Ressource.cpp \
				menu.cpp \
				Player.cpp \
				Tiles.cpp \
				Egg.cpp \
				Communication.cpp \
				GraphicClient.cpp \
				main.cpp)

OBJDIR		=		build

OBJS		=		$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o,  $(SRCS))

all:		$(NAME)
		@echo "Done compiling $(NAME)"

$(NAME):	buildrepo $(OBJS)
		@echo "Linking $(NAME)"
		@$(CXX) $(CXXFLAGS) $(OUTPUT_OPTION) $(OBJS) $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o:	$(SRCDIR)/%.cpp
		@echo "->" $<
		@$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $(OUTPUT_OPTION) $^

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
