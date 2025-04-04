LIBFT_DIR = Libft
GNL_DIR = get_next_line

LIB_NAME = lib.a

all: $(LIB_NAME)

$(LIB_NAME): libft gnl
	@echo "Creating the library: $(LIB_NAME)"
	@ar rcs $(LIB_NAME) $(LIBFT_DIR)/*.o $(GNL_DIR)/*.o

libft:
	@echo "Compiling Libft.."
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory --silent

gnl:
	@echo "Compiling get_next_line.."
	@$(MAKE) -C $(GNL_DIR) --no-print-directory --silent

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory --silent

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory --silent
	@rm -f $(LIB_NAME)

re: fclean all

.PHONY: all libft clean fclean re
