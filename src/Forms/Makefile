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

SRC					=	AxisAlignedBoundingBox.cpp
SRC					+=	HitRecord.cpp
SRC					+=	../Ray.cpp

SRC_BOX				=	3D/Box.cpp
SRC_BOX				+=	FormFactory.cpp
SRC_BOX				+=	FormList.cpp
SRC_BOX				+=	$(SRC)

OBJ_BOX				=	$(SRC_BOX:.cpp=.o)

NAME_BOX			=	../../libs/Forms/3D/Box.so

SRC_CONSTANT_MEDIUM	=	Instances/ConstantMedium.cpp
SRC_CONSTANT_MEDIUM	+=	../Materials/MaterialFactory.cpp
SRC_CONSTANT_MEDIUM	+=	$(SRC)

OBJ_CONSTANT_MEDIUM	=	$(SRC_CONSTANT_MEDIUM:.cpp=.o)

NAME_CONSTANT_MEDIUM=	../../libs/Forms/Instances/ConstantMedium.so

SRC_CUBE			=	3D/Cube.cpp
SRC_CUBE			+=	$(SRC)

OBJ_CUBE			=	$(SRC_CUBE:.cpp=.o)

NAME_CUBE			=	../../libs/Forms/3D/Cube.so

SRC_CYLINDER		=	3D/Cylinder.cpp
SRC_CYLINDER		+=	$(SRC)

OBJ_CYLINDER		=	$(SRC_CYLINDER:.cpp=.o)

NAME_CYLINDER		=	../../libs/Forms/3D/Cylinder.so

SRC_MOVING_SPHERE	=	3D/MovingSphere.cpp
SRC_MOVING_SPHERE	+=	$(SRC)

OBJ_MOVING_SPHERE	=	$(SRC_MOVING_SPHERE:.cpp=.o)

NAME_MOVING_SPHERE	=	../../libs/Forms/3D/MovingSphere.so

SRC_RECTANGLEXY		=	2D/RectangleXY.cpp
SRC_RECTANGLEXY		+=	$(SRC)

OBJ_RECTANGLEXY		=	$(SRC_RECTANGLEXY:.cpp=.o)

NAME_RECTANGLEXY	=	../../libs/Forms/2D/RectangleXY.so

SRC_RECTANGLEXZ		=	2D/RectangleXZ.cpp
SRC_RECTANGLEXZ		+=	$(SRC)

OBJ_RECTANGLEXZ		=	$(SRC_RECTANGLEXZ:.cpp=.o)

NAME_RECTANGLEXZ	=	../../libs/Forms/2D/RectangleXZ.so

SRC_RECTANGLEYZ		=	2D/RectangleYZ.cpp
SRC_RECTANGLEYZ		+=	$(SRC)

OBJ_RECTANGLEYZ		=	$(SRC_RECTANGLEYZ:.cpp=.o)

NAME_RECTANGLEYZ	=	../../libs/Forms/2D/RectangleYZ.so

SRC_ROTATEX			=	Instances/RotateX.cpp
SRC_ROTATEX			+=	$(SRC)

OBJ_ROTATEX			=	$(SRC_ROTATEX:.cpp=.o)

NAME_ROTATEX		=	../../libs/Forms/Instances/RotateX.so

SRC_ROTATEY			=	Instances/RotateY.cpp
SRC_ROTATEY			+=	$(SRC)

OBJ_ROTATEY			=	$(SRC_ROTATEY:.cpp=.o)

NAME_ROTATEY		=	../../libs/Forms/Instances/RotateY.so

SRC_ROTATEZ			=	Instances/RotateZ.cpp
SRC_ROTATEZ			+=	$(SRC)

OBJ_ROTATEZ			=	$(SRC_ROTATEZ:.cpp=.o)

NAME_ROTATEZ		=	../../libs/Forms/Instances/RotateZ.so

SRC_SPHERE			=	3D/Sphere.cpp
SRC_SPHERE			+=	$(SRC)

OBJ_SPHERE			=	$(SRC_SPHERE:.cpp=.o)

NAME_SPHERE			=	../../libs/Forms/3D/Sphere.so

SRC_TRANSLATE		=	Instances/Translate.cpp
SRC_TRANSLATE		+=	$(SRC)

OBJ_TRANSLATE		=	$(SRC_TRANSLATE:.cpp=.o)

NAME_TRANSLATE		=	../../libs/Forms/Instances/Translate.so

INC			=	-I../../include/
INC			+=	-I../../include/Forms
INC			+=	-I../../include/Forms/Instances
INC			+=	-I../../include/Forms/2D
INC			+=	-I../../include/Forms/3D
INC			+=	-I../../include/Math
INC			+=	-I../../include/Materials
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
	@printf "%b" "$(ERROR_COLOR)Compiling Forms...\n$(NO_COLOR)"
	@printf "%b" "$(ERROR_COLOR)\tCompiling Box...\n$(NO_COLOR)"
	@make compile_box -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_BOX) $(OBJ_BOX) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling ConstantMedium...\n$(NO_COLOR)"
	@make compile_constantmedium -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_CONSTANT_MEDIUM) $(OBJ_CONSTANT_MEDIUM) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling Cube...\n$(NO_COLOR)"
	@make compile_cube -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_CUBE) $(OBJ_CUBE) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling Cylinder...\n$(NO_COLOR)"
	@make compile_cylinder -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_CYLINDER) $(OBJ_CYLINDER) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling MovingSphere...\n$(NO_COLOR)"
	@make compile_movingsphere -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_MOVING_SPHERE) $(OBJ_MOVING_SPHERE) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling RectangleXY...\n$(NO_COLOR)"
	@make compile_rectanglexy -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_RECTANGLEXY) $(OBJ_RECTANGLEXY) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling RectangleXZ...\n$(NO_COLOR)"
	@make compile_rectanglexz -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_RECTANGLEXZ) $(OBJ_RECTANGLEXZ) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling RectangleYZ...\n$(NO_COLOR)"
	@make compile_rectangleyz -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_RECTANGLEYZ) $(OBJ_RECTANGLEYZ) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling RotateX...\n$(NO_COLOR)"
	@make compile_rotatex -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_ROTATEX) $(OBJ_ROTATEX) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling RotateY...\n$(NO_COLOR)"
	@make compile_rotatey -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_ROTATEY) $(OBJ_ROTATEY) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling RotateZ...\n$(NO_COLOR)"
	@make compile_rotatez -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_ROTATEZ) $(OBJ_ROTATEZ) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling Sphere...\n$(NO_COLOR)"
	@make compile_sphere -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_SPHERE) $(OBJ_SPHERE) $(INC) $(LIB)
	@printf "%b" "$(ERROR_COLOR)\tCompiling Translate...\n$(NO_COLOR)"
	@make compile_translate -s
	@$(CXX) $(CXXFLAGS) -o $(NAME_TRANSLATE) $(OBJ_TRANSLATE) $(INC) $(LIB)
	@printf "%b" "$(OK_COLOR)Forms compiled !\n$(NO_COLOR)"

%.o: %.cpp
	@$(call run_and_test, $(CXX) $(CXXFLAGS) -c $< -o $@ $(INC) $(LIB))

compile_box: $(OBJ_BOX)

compile_constantmedium: $(OBJ_CONSTANT_MEDIUM)

compile_cube: $(OBJ_CUBE)

compile_cylinder: $(OBJ_CYLINDER)

compile_movingsphere: $(OBJ_MOVING_SPHERE)

compile_rectanglexy: $(OBJ_RECTANGLEXY)

compile_rectanglexz: $(OBJ_RECTANGLEXZ)

compile_rectangleyz: $(OBJ_RECTANGLEYZ)

compile_rotatex: $(OBJ_ROTATEX)

compile_rotatey: $(OBJ_ROTATEY)

compile_rotatez: $(OBJ_ROTATEZ)

compile_sphere: $(OBJ_SPHERE)

compile_translate: $(OBJ_TRANSLATE)

clean:
	@$(RM) $(OBJ_BOX) $(OBJ_CONSTANT_MEDIUM) $(OBJ_CUBE) $(OBJ_CYLINDER) \
		$(OBJ_MOVING_SPHERE) $(OBJ_RECTANGLEXY) $(OBJ_RECTANGLEXZ) \
		$(OBJ_RECTANGLEYZ) $(OBJ_ROTATEX) $(OBJ_ROTATEY) $(OBJ_ROTATEZ) \
		$(OBJ_SPHERE) $(OBJ_TRANSLATE)
	@printf "%-95b%b" "$(CLEAN_COLOR)Forms cleaned !" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

fclean: clean
	@$(RM) $(NAME_BOX) $(NAME_CONSTANT_MEDIUM) $(NAME_CUBE) $(NAME_CYLINDER) \
		$(NAME_MOVING_SPHERE) $(NAME_RECTANGLEXY) $(NAME_RECTANGLEXZ) \
		$(NAME_RECTANGLEYZ) $(NAME_ROTATEX) $(NAME_ROTATEY) $(NAME_ROTATEZ) \
		$(NAME_SPHERE) $(NAME_TRANSLATE)
	@printf "%-95b%b" "$(FCLEAN_COLOR)Forms fcleaned !" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re
