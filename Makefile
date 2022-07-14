
##
## EPITECH PROJECT, 2021
## MAKEFILE
## File description:
## DEFENDER
##

NAME	= 	plazza

# COLOR CODE #

RED			=	\e[91m
BLUE		=	[39m[38;5;33m
TURQUOISE	=	\e[96m
GREEN		=	\e[32m
BLINK_RED	=	\e[91;5m
BOLD_GREEN	=	\e[32;1m
NO_BLINK	=	\e[25m
VIOLET		=	[39m[38;5;63m
END			=	\e[0m
VERTCLAIR	=	[39m[38;5;155m
ORANGE		=	[39m[38;5;220m
NUAGE		=	[39m[38;5;153m
ROUGE_SANS 	=	[39m[38;5;196m
BLEU_FONCER	=	[39m[38;5;12m
JAUNE		=	[39m[38;5;226m
ROSE		=	[39m[38;5;198m
POURPRE		=	[39m[38;5;183m

# PRINT MODE #

CREATE_FILST_TIME = echo "$(BLUE)** CREATE FIRST TIME $(NAME) **$(END)"
CREATE_FILST_TIME_END = echo "$(BLUE)** CREATE FIRST TIME $(NAME) END **$(END)"

VPATH+= src/:./
VPATH+= src/util/:./

SRC 	+= 		utils.cpp 		\
				Plazza.cpp		\
				Serveur.cpp		\
				Client.cpp		\
				Reception.cpp	\
				Kitchen.cpp		\
				Parser.cpp		\
				Cook.cpp		\

ifneq ($(MAKECMDGOALS), tests_run)
ifneq ($(MAKECMDGOALS), test)
SRC	+=	main.cpp
endif
endif

TESTS	+= 	\

HEADERS_DIR	= include/ include/util include/res

ADD_HEADERS_DIR = $(addprefix -I./, $(HEADERS_DIR))

PROJECT := $(shell realpath .)

USER := $(shell whoami)

CXXFLAGS	+= 	$(ADD_HEADERS_DIR) -Wall -W -Wextra -std=c++11

LIB		=	-pthread

ifeq ($(MAKECMDGOALS), test)
SRC_TEST+= $(TESTS)
CXXFLAGS	+= 	--coverage -lcriterion
CXXFLAGS	+=  -g3
LIB		=	-lm -pthread

endif

CXXFLAGS	+=  -g3

ifeq ($(MAKECMDGOALS), tests_run)
SRC_TEST+= $(TESTS)
CXXFLAGS	+= 	--coverage -lcriterion
CXXFLAGS	+=  -g3
LIB		=	-lm -pthread

endif

ifeq ($(MAKECMDGOALS), exec_debug)
CXXFLAGS	+=  -g3
endif

SRC_TEST+=

FIND_build = $(shell find . -type d | grep build)

AR								=	ar rc

RM								=	rm -f

ifeq ($(MAKECMDGOALS), test)
LIB							+= 	--coverage -lcriterion
endif
ifeq ($(MAKECMDGOALS), tests_run)
LIB								+= 	--coverage -lcriterion
endif

define test_fonctionnel =
#!/bin/bash
	ret_test=0
	font_black_purple="\033[38;5;13m"
	font_normal="\033[40;37;0m"
	font_big_noir_bleu_foncer="\033[38;5;33;1m"

	if [ -e build_find_error ]; then
		test -s build_find_error
		ret_test=$(echo $?)
		# echo $ret_test
		if [ $ret_test -eq 0 ]; then
			echo "${font_black_purple}** NOFINK TO DO ON THE PROJECT ** \
			${font_normal}"
		else
			echo "${font_big_noir_bleu_foncer} \
			** SOMEFINK WAS MODIFIE ON THE PROJECT **${font_normal}"
		fi
	fi
endef

vpath %.o build

OBJ	= $(SRC:.cpp=.o)

all : $(NAME)

.PHONY: debug
debug :
	@make -s fclean -C ./
	@clear
	@make exec_debug -s -C ./

%.o:	%.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $< && (echo "\e[32m[OK]\033[0m\e[1m\e[32m" \
	"$(BLUE)" "$(CXXFLAGS)" "\e[32m" $< "\033[0m") || (echo \
	"\e[91;5m[KO]\e[25m" $<)

.PHONY: check_build_file
check_build_file :	$(OBJ)
	@if [ ! -e "build" ]; then mkdir build/; mv $(OBJ) build/; \
	${CREATE_FILST_TIME_END}; $(RM) build_find_error; \
	else mv -f *.o build 2> build_find_error; true; fi

.PHONY: is_create_build
is_create_build: $(FIND_build)
	@if [ ! -e "build" ]; then $(CREATE_FILST_TIME); fi

.PHONY: init_lib
init_lib:

.PHONY: run_makefile
run_makefile:
	@echo "$(ROSE)_____$(JAUNE)BEGIN MAKEFILE: $(BLEU_FONCER) \
	$(PROJECT)$(ROSE)_____$(END)"

.PHONY: stop_makefile
stop_makefile:
	@echo "$(ROSE)_____$(JAUNE)END MAKEFILE: $(BLEU_FONCER) \
	$(PROJECT)$(ROSE)_____ $(POURPRE)$(USER)$(END)"

.PHONY: compile
compile:	$(OBJ)
	@$(CXX) -o $(NAME) $(addprefix build/, $(OBJ)) $(SRC_TEST) \
	$(LIB) $(ADD_HEADERS_DIR) && (echo "$(VERTCLAIR) $(CXX) $(ORANGE) \
	$(NAME) $(NUAGE) $(addprefix build/, $(OBJ)) $(ROUGE_SANS) \
	$(LIB) $(END)") || (echo "$(ROUGE_SANS) **BUILD FAIL** $(END)")

$(NAME): run_makefile init_lib is_create_build $(OBJ) check_build_file \
	rite_test compile stop_makefile

.PHONY: tests_run
tests_run : $(NAME)
	@./$(NAME)

.PHONY: test
test	: tests_run
	@clear
	@-@gcovr --exclude tests/
	@-@gcovr --branch --exclude tests/

.PHONY: clean
clean:
	@$(RM)	$(NAME)
	@$(RM) 	build_find_error
	$(RM) *gcno *gcda

.PHONY: fclean
fclean: clean
	@rm -rf build
	@$(RM) $(OBJ)
	$(RM) *gcno *gcda

.PHONY: rite_test
rite_test: ; @$(value test_fonctionnel)
	@$(RM) 	build_find_error

.PHONY: re
re:
	@make -s fclean -C ./
	@make -s -C ./

.ONESHELL:
