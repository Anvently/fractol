NAME		=	fractol
BONUS_NAME	=

INCLUDES	=	includes/
SRCS_FOLDER	=	sources/
OBJS_FOLDER	=	objects/

SRCS_FILES	=	main.c

OBJS		=	$(addprefix $(OBJS_FOLDER),$(SRCS_FILES:.c=.o))
SRCS		=	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))

LIBFT		=	libft/libft.a
LIBMLX		=	libmlx/libmlx.a

DEPS		=	$(LIBFT) $(LIBMLX) $(INCLUDES)libft.h $(INCLUDES)mlx.h $(INCLUDES)mlx_int.h

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 -I$(INCLUDES)

.PHONY		=	all clean fclean test re bonus

all: $(NAME)

$(NAME): $(DEPS) $(OBJS)
	@echo "\n-----COMPILING $(NAME)-------\n"
	$(CC) $(CFLAGS) $(OBJS) -Llibft/ -lft -Llibmlx/ -lmlx -lXext -lX11 -lm -o $(NAME)
	@echo "Executable has been successfully created."

bonus: $(BONUS_NAME)

$(OBJS_FOLDER)%.o: $(SRCS_FOLDER)%.c Makefile $(INCLUDES)$(NAME).h $(DEPS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(INCLUDES)libft.h: libft/libft.h
	@echo "------ UPDATING LIBFT HEADER -------\n"
	cp libft/libft.h $(INCLUDES)libft.h

$(INCLUDES)mlx.h: libmlx/mlx.h
	@echo "------ UPDATING MLX HEADER -------\n"
	cp libmlx/mlx.h $(INCLUDES)mlx.h

$(INCLUDES)mlx_int.h: libmlx/mlx_int.h
	@echo "------ UPDATING MLX HEADER -------\n"
	cp libmlx/mlx_int.h $(INCLUDES)mlx_int.h

$(LIBFT): $(INCLUDES)libft.h
	@echo "\n-------COMPILING LIBFT--------------\n"
	make -C libft/
	make clean -C libft/
	@echo "\n\n"

$(LIBMLX): $(INCLUDES)mlx.h
	@echo "\n-------COMPILING MINILIBX--------------\n"
	make -C libmlx/
	make clean -C libmlx/
	@echo "\n\n"


clean:
	@echo "\n-------------CLEAN--------------\n"
	make clean -C libft/
	rm -rf $(OBJS_FOLDER)
	@echo "object files have been removed."

fclean: clean
	@echo "\n-------------FORCE CLEAN--------------\n"
	make fclean -C libft/
	rm -rf $(NAME) $(BONUS_NAME)
	@echo "$(NAME) and object files have been removed."

re: fclean all
