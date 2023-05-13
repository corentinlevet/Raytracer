##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile for the Raytracer project
##

###############################################################################
#                                     CONFIG                                  #
###############################################################################

CXX			=	g++

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++20 -pedantic -fPIC -fno-gnu-unique

LDFLAGS		=	-ldl -lconfig++ -lsfml-graphics -lsfml-window -lsfml-system

AUTHOR		=	Corentin LEVET - Benjamin COTTONE - Hugo GRISEL\
				- Jeremy CALOSSO-MERLINO

RM			=	rm -rf

###############################################################################
#                                    SOURCES                                  #
###############################################################################

SRC		=	$(wildcard src/*.cpp)				\
			$(wildcard src/Camera/*.cpp)		\
			$(wildcard src/Forms/*.cpp)			\
			src/Lights/LightFactory.cpp			\
			src/Materials/MaterialFactory.cpp	\
			src/Textures/TextureFactory.cpp		\

OBJ		=	$(SRC:.cpp=.o)

NAME	=	raytracer

INC		=	-I./include
INC		+=	-I./include/Camera
INC		+=	-I./include/Forms
INC		+=	-I./include/Lights
INC		+=	-I./include/Math
INC		+=	-I./include/Materials
INC		+=	-I./include/Textures

LIB 	=	-L./libs/Math -l:Math.a

###############################################################################
#                                MAKEFILE LOGIC                               #
###############################################################################

NO_COLOR    	=	\033[m
FCLEAN_COLOR 	=	\033[31;1m
ERROR_COLOR 	=	\033[31;1m
OK_COLOR    	=	\033[32;1m
WARN_COLOR  	=	\033[33;1m
COM_COLOR   	=	\033[34;1m
CLEAN_COLOR 	=	\033[35;1m
OBJ_COLOR   	=	\033[36;1m

COM_STRING   	=	"Compiling"

ifeq ($(OS), Windows_NT)
    detected_OS	:= Windows
else
    detected_OS	:= $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS),Darwin)
	RUN_CMD	= script -q $@.log $1 > /dev/null;							\
	RESULT=$$?
else ifeq ($(detected_OS),Linux)
	RUN_CMD	= script -q -e -c "$(1)" $@.log > /dev/null; 				\
	RESULT=$$?;															\
	sed -i '1d' $@.log;													\
	sed -i "$$(($$(wc -l < $@.log)-1)),\$$d" $@.log
else
	RUN_CMD = $(1) 2> $@.log;											\
	RESULT=$$?
endif

ifeq ($(shell git rev-parse HEAD &>/dev/null; echo $$?),0)
	DATE	:= $(shell git log -1 --date=format:"%Y/%m/%d %T" 			\
				--format="%ad")
endif

define run_and_test
	printf "%b%-88b" "$(COM_COLOR)$(COM_STRING) "						\
		"$(OBJ_COLOR)$(@F)$(NO_COLOR)"; 								\
	$(RUN_CMD);															\
	if [ $$RESULT -ne 0 ]; then											\
		printf "%b\n" "$(ERROR_COLOR)[✖]$(NO_COLOR)";				    \
		rm -rf .files_changed;											\
		if [ $(NOVISU) -eq 0 ]; then									\
			echo;														\
		fi;																\
	elif [ -s $@.log ]; then											\
		printf "%b\n" "$(WARN_COLOR)[⚠]$(NO_COLOR)";					\
	else																\
		printf "%b\n" "$(OK_COLOR)[✓]$(NO_COLOR)";						\
	fi;																	\
	cat $@.log;															\
	rm -f $@.log;														\
	exit $$RESULT
endef

###############################################################################
#                                 Makefile rules                              #
###############################################################################

all:	header $(OBJ) math forms materials textures lights
	@$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS) $(INC) $(LIB) $(LDFLAGS)
	@printf "\n%b" "$(OK_COLOR)Compilation done !\n$(NO_COLOR)"

bonus: all
	@printf "\n"
	@make -s -C bonus/PPMtoPNG

src/%.o:	src/%.cpp
	@$(call run_and_test, $(CXX) $(CXXFLAGS) $(INC) $(LIB) $(LDFLAGS) -c $< -o $@)

header:
	@printf "\n%b" "$(OBJ_COLOR)Name\t:\t$(WARN_COLOR)$(NAME)\n"

	@printf "%b" "$(OBJ_COLOR)Author\t:\t$(WARN_COLOR)$(AUTHOR)\n"
	@printf "%b" "$(OBJ_COLOR)Date\t:\t$(WARN_COLOR)$(DATE)\n\033[m"
	@printf "%b" "$(OBJ_COLOR)CC\t:\t$(WARN_COLOR)$(CXX)\n\033[m"
	@printf "%b" "$(OBJ_COLOR)Flags\t:\t$(WARN_COLOR)$(CXXFLAGS)\n\033[m"
	@printf "%b" "$(OBJ_COLOR)Libs\t:\t$(WARN_COLOR)$(LDFLAGS)\n\033[m"
	@echo

forms:
	@printf "\n"
	@make -s -C src/Forms

lights:
	@printf "\n"
	@make -s -C src/Lights

math:
	@printf "\n"
	@make -s -C src/Math

materials:
	@printf "\n"
	@make -s -C src/Materials

textures:
	@printf "\n"
	@make -s -C src/Textures

clean:
	@make -s clean -C bonus/PPMtoPNG &>/dev/null
	@make -s clean -C src/Forms &>/dev/null
	@make -s clean -C src/Lights &>/dev/null
	@make -s clean -C src/Math &>/dev/null
	@make -s clean -C src/Materials &>/dev/null
	@make -s clean -C src/Textures &>/dev/null
	@$(RM) $(OBJ)
	@printf "%-95b%b" "$(CLEAN_COLOR)clean" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

fclean:	clean
	@make -s fclean -C bonus/PPMtoPNG &>/dev/null
	@make -s fclean -C src/Forms &>/dev/null
	@make -s fclean -C src/Lights &>/dev/null
	@make -s fclean -C src/Math &>/dev/null
	@make -s fclean -C src/Materials &>/dev/null
	@make -s fclean -C src/Textures &>/dev/null
	@$(RM) $(NAME)
	@printf "%-95b%b" "$(FCLEAN_COLOR)fclean" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

re:	fclean all

.PHONY:	all clean fclean re
