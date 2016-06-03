NAME = rtv1

#==============#
#_- Compiler -_#
#==============#
CC = gcc
CFLAGS = -Werror -Wall -Wextra -g
RM = rm -rf
MAKE = make -sC

#====================#
#_- Programes Path -_#
#====================#
SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./include/
LIB_PATH =

#=================#
#_- lib externe -_#
#=================#
FRAMEWORK = -framework Opengl -framework Appkit

MINILIBX_PATH = ./minilibx/
MINILIBX = -L$(MINILIBX_PATH) -lmlx
INC_MINILIBX = -I$(MINILIBX_PATH)

LIBFT_PATH = ./libft/
LIBFT = -L$(LIBFT_PATH) -lft
INC_LIBFT = -I$(LIBFT_PATH)/include/

#===========#
#_- Color -_#
#===========#

# color #
# red = 9
# hard_red = 196
# orange = 214
# violet = 140
# green = 47

TITLE_COLOR = 214
CLEAN_COLOR = 9
LINK_COLOR = 47
OBJ_COLOR = 47

MAKE_COLOR = 47
MAKE_ALREADY = 140
MAKE_FAIL = 9

NORME_COLOR = 47
NORME_COLOR_ERR = 9
NORME_COLOR_WAR = 196

#==============#
#_- Fonction -_#
#==============#

cmd_make = echo "\033[38;5;$(MAKE_COLOR)m$(MAKE) $(1)\033[0m"; \
		   $(MAKE) $(1)

cmd_color = echo "\033[38;5;$(1)m$(2)\033[0m"; \
			$(2)

put_title = echo "\033[38;5;$(TITLE_COLOR)m[ $(1) ]\033[0m"

#==================#
#_- Source Files -_#
#==================#

PARSER_PATH = parser/
PARSER_FILES = parsing.c \
			   camera_parsing.c \
			   plane_parsing.c \
			   sphere_parsing.c \
			   cone_parsing.c \
			   cube_parsing.c \
			   tore_parsing.c \
			   quadra_parsing.c \
			   pobj_parsing.c \
			   pobj_parsing2.c \
			   pobj_parsing3.c \
			   cylinder_parsing.c \
			   light_parsing.c \
			   config_parsing.c \
			   mat_parsing.c \
			   equ_parsing.c \
			   noise.c \
			   noise_parser.c \
			   obj_composed.c \
			   obj_composed_2.c\
			   obj_composed_3.c\
			   predefine_obj.c \
			   scene_parsing.c \
			   parsing_utils.c

PARSER = $(addprefix $(PARSER_PATH), $(PARSER_FILES))
PARSER_OBJ_PATH = $(addprefix $(OBJ_PATH), $(PARSER_PATH))

SRC_NAME = main.c \
		   ft_put_pixelle.c \
		   ft_creat_win.c \
		   ft_cal_gen.c \
		   ft_texture.c \
		   ft_texture2.c \
		   ft_texture3.c \
		   ft_angle_contact.c \
		   ft_angle_contact2.c \
		   ft_brillance.c \
		   ft_shadow.c \
		   ft_shadow2.c \
		   ft_shadow3.c \
		   ft_dist.c \
		   ft_dist2.c \
		   ft_dist3.c \
		   ft_dist4.c \
		   ft_dist5.c \
		   ft_math.c \
		   ft_math2.c \
		   ft_math3.c \
		   ft_rotate.c \
		   utils.c \
		   ft_screen_shot.c \
		   ft_antialiasing.c \
		   ft_correction.c \
		   ft_celshading.c \
		   ft_ref.c \
		   ft_op_composed_obj.c \
		   ft_op_composed_obj2.c \
		   ft_motion_blur.c \
			$(PARSER)


OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

INC = $(addprefix -I, $(INC_PATH)) $(INC_MINILIBX) $(INC_LIBFT)

LDFLAGS = $(addprefix -L, $(LIB_PATH)) $(LIBFT) $(MINILIBX) $(FRAMEWORK)

#===========#
#_- Rules -_#
#===========#
all: $(NAME)

#	linking
$(OBJ_PATH)%.o:  $(SRC_PATH)%.c
	@$(call cmd_color,$(LINK_COLOR),$(CC) $(CFLAGS) $(INC) -o $@ -c $<)

#	preLinking
$(OBJ_PATH):
	@$(call put_title,Linking)
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(PARSER_OBJ_PATH)

#	Object Compiation
$(NAME): $(OBJ_PATH) $(OBJ)
	@$(call put_title,Compilation)
	@$(call cmd_make,$(LIBFT_PATH))
	@$(call cmd_make,$(MINILIBX_PATH))
	@$(call cmd_color,$(OBJ_COLOR),$(CC) $(LDFLAGS) $(OBJ) -o $@)

#	Removing object
clean:
	@$(call put_title,Cleaning)
	@$(RM) $(OBJ_PATH)
	@make -C ./libft clean
	@$(call cmd_color,$(CLEAN_COLOR),rm -rf $(OBJ))

#	Removeing binary
fclean : clean
	@$(RM) $(NAME)
	@$(call cmd_color,$(CLEAN_COLOR),rm -rf $(NAME))
	@make -C ./libft fclean

re: fclean all

#	check norme for includes and ./srcs/ files
norme:
	@norminette $(SRC) $(INC_PATH) | sed "s/Norme/[0;1;47m\
	[0;38;5;$(NORME_COLOR)mNorme/g; s/Warning/[38;5;$(NORME_COLOR_WAR)m\
	Warning/g; s/Error/\[38;5;$(NORME_COLOR_ERR)m Error/g"

#	run the program
run: all
	@echo "\033[38;5;214mRuning Test:\033[0m"
	@./$(NAME)

.PHONY: all clean fclean re norme run
