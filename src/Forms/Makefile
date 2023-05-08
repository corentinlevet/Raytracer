##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile for the Forms of the Raytracer project
##

###############################################################################
#                                     CONFIG                                  #
###############################################################################

CXX			=	g++

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++20 -pedantic	\
				-fPIC -fno-gnu-unique -shared

AUTHOR		=	Corentin LEVET - Benjamin COTTONE - Hugo GRISEL\
				- Jeremy CALOSSO-MERLINO

RM			=	rm -rf

###############################################################################
#                                    SOURCES                                  #
###############################################################################

SRC			=	HitRecord.cpp
SRC			+=	../Ray.cpp

SRC_CUBE	=	3D/Cube.cpp
SRC_CUBE	+=	$(SRC)

OBJ_CUBE	=	$(SRC_CUBE:.cpp=.o)

NAME_CUBE	=	../../libs/Forms/3D/Cube.so

SRC_SPHERE	=	3D/Sphere.cpp
SRC_SPHERE	+=	$(SRC)

OBJ_SPHERE	=	$(SRC_SPHERE:.cpp=.o)

NAME_SPHERE	=	../../libs/Forms/3D/Sphere.so

INC			=	-I../../include/
INC			+=	-I../../include/Forms
INC			+=	-I../../include/Forms/3D
INC			+=	-I../../include/Math
INC			+=	-I../../include/Materials

LIB         =   -L../../libs/Math -l:Math.a

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
	printf "\t%b%-80b" "$(COM_COLOR)$(COM_STRING) "						\
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

define check_math
	if [ ! -f ../../libs/Math/Math.a ]; then							\
		make -s -C ../Math;												\
		printf "\n";													\
	fi;
endef

###############################################################################
#                                 Makefile rules                              #
###############################################################################

all:
	@$(call check_math)
	@printf "%b" "$(ERROR_COLOR)Compiling Forms...\n$(NO_COLOR)"
	@printf "%b" "$(ERROR_COLOR)\tCompiling Cube...\n$(NO_COLOR)"
	@make compile_cube -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_CUBE) $(OBJ_CUBE) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling Sphere...\n$(NO_COLOR)"
	@make compile_sphere -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_SPHERE) $(OBJ_SPHERE) $(INC) $(LIB)
	@printf "%b" "$(OK_COLOR)Forms compiled !\n$(NO_COLOR)"

%.o: %.cpp
	@$(call run_and_test, $(CXX) $(CXXFLAGS) -c $< -o $@ $(INC) $(LIB))

compile_cube: $(OBJ_CUBE)

compile_sphere: $(OBJ_SPHERE)

clean:
	@$(RM) $(OBJ_CUBE) $(OBJ_SPHERE)
	@printf "%-95b%b" "$(CLEAN_COLOR)Forms cleaned !" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

fclean: clean
	@$(RM) $(NAME_CUBE) $(NAME_SPHERE)
	@printf "%-95b%b" "$(FCLEAN_COLOR)Forms fcleaned !" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re
