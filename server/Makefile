APP_NAME = chat_server

LIBMXF = libmx/libmx.a

JSONF = src/json-c

JSON_NAME = libjson-c.a

INC = inc/ \
	  src/json-c-build/

SRC_DIR = src

OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/,\
      		main.c \
      		mx_sqlite.c \
      		mx_socket.c \
      		mx_printerr.c )


OBJ = main.o \
      mx_sqlite.o \
      mx_socket.o \
      mx_printerr.o

CC = clang

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic #-g3 -fsanitize=address

all : install

install : json uchat

json:
	@make -C $(JSONF)

uchat : $(SRC) inc/header.h libmx/libmx.a src/json-c/libjson-c.a
	@$(CC) $(CFLAGS) -c $(SRC) $(foreach d, $(INC), -I $d)
	@$(CC) $(CFLAGS) $(OBJ) $(JSONF)/$(JSON_NAME) $(LIBMXF) -l sqlite3 -o $(APP_NAME)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"
	@mkdir -p $(OBJ_DIR)
	@mv $(OBJ) $(OBJ_DIR)
	@rm -rf ./*.c ./*.h
	@rm -rf $(OBJ_DIR)
	@printf "$(NAME) \033[31;1minstalled\033[0m\n"

uninstall : clean
	@make uninstall -C $(JSONF)
	@rm -rf $(APP_NAME)
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

clean :

	@make clean -C $(JSONF)
	@rm -rf $(OBJ_DIR)
	@printf "$(OBJD)\t   \033[31;1mdeleted\033[0m\n"

reinstall : uninstall install


