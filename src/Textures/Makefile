##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile for the Textures of the Raytracer project
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

SRC			=	../Forms/HitRecord.cpp

SRC_CHECKER     =  	Checker.cpp
SRC_CHECKER     +=  TextureFactory.cpp
SRC_CHECKER     +=  $(SRC)

OBJ_CHECKER	 	=   $(SRC_CHECKER:.cpp=.o)

NAME_CHECKER	=	../../libs/Textures/Checker.so

SRC_IMAGE		=	ImageTexture.cpp
SRC_IMAGE		+=	$(SRC)

OBJ_IMAGE		=	$(SRC_IMAGE:.cpp=.o)

NAME_IMAGE		=	../../libs/Textures/ImageTexture.so

SRC_PERLIN		=	Perlin.cpp
SRC_PERLIN		+=	$(SRC)

OBJ_PERLIN		=	$(SRC_PERLIN:.cpp=.o)

NAME_PERLIN		=	../../libs/Textures/Perlin.so

SRC_SOLIDCOLOR	=	SolidColor.cpp
SRC_SOLIDCOLOR	+=	$(SRC)

OBJ_SOLIDCOLOR	=	$(SRC_SOLIDCOLOR:.cpp=.o)

NAME_SOLIDCOLOR	=	../../libs/Textures/SolidColor.so

INC			=	-I../../include/
INC			+=	-I../../include/Forms
INC			+=	-I../../include/Materials
INC			+=	-I../../include/Math
INC			+=	-I../../include/Textures

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
	@printf "%b" "$(ERROR_COLOR)Compiling Textures...\n$(NO_COLOR)"
	@printf "%b" "$(ERROR_COLOR)\tCompiling Checker...\n$(NO_COLOR)"
	@make compile_checker -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_CHECKER) $(OBJ_CHECKER) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling ImageTexture...\n$(NO_COLOR)"
	@make compile_image -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_IMAGE) $(OBJ_IMAGE) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling Perlin...\n$(NO_COLOR)"
	@make compile_perlin -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_PERLIN) $(OBJ_PERLIN) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling SolidColor...\n$(NO_COLOR)"
	@make compile_solidcolor -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_SOLIDCOLOR) $(OBJ_SOLIDCOLOR) $(INC) $(LIB)
	@printf "%b" "$(OK_COLOR)Textures compiled !\n$(NO_COLOR)"

%.o: %.cpp
	@$(call run_and_test, $(CXX) $(CXXFLAGS) -c $< -o $@ $(INC) $(LIB))

compile_checker: $(OBJ_CHECKER)

compile_image: $(OBJ_IMAGE)

compile_perlin: $(OBJ_PERLIN)

compile_solidcolor: $(OBJ_SOLIDCOLOR)

clean:
	@$(RM) $(OBJ_CHECKER) $(OBJ_IMAGE) $(OBJ_PERLIN) $(OBJ_SOLIDCOLOR)
	@printf "%-95b%b" "$(CLEAN_COLOR)Textures cleaned !" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

fclean: clean
	@$(RM) $(NAME_CHECKER) $(NAME_IMAGE) $(NAME_PERLIN) $(NAME_SOLIDCOLOR)
	@printf "%-95b%b" "$(FCLEAN_COLOR)Textures fcleaned !" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re
