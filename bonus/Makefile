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

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++20

LDFLAGS		=	-lpng

AUTHOR		=	Corentin LEVET - Benjamin COTTONE - Hugo GRISEL\
				- Jeremy CALOSSO-MERLINO

RM			=	rm -rf

###############################################################################
#                                    SOURCES                                  #
###############################################################################

SRC		=	$(wildcard src/*.cpp)				\

OBJ		=	$(SRC:.cpp=.o)

NAME	=	PPMtoPNG

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

all:	header $(OBJ)
	@$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS) $(LDFLAGS)
	@printf "\n%b" "$(OK_COLOR)Compilation done !\n$(NO_COLOR)"

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

clean:
	@$(RM) $(OBJ)
	@printf "%-95b%b" "$(CLEAN_COLOR)clean" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

fclean:	clean
	@$(RM) $(NAME)
	@printf "%-95b%b" "$(FCLEAN_COLOR)fclean" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

re:	fclean all

.PHONY:	all clean fclean re
