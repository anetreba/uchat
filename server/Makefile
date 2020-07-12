APP_NAME = chat_server

LIBMXF = libmx/libmx.a

JSONF = json-c

JSON_NAME = libjson-c.a

INC = inc/ \
	  json-c/inc/

SRC_DIR = src

OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/,\
		main.c \
		mx_sqlite.c \
		mx_socket.c \
		mx_printerr.c \
		mx_event.c  \
		mx_parse_json.c \
		models/mx_model_insert.c \
		models/mx_model_select.c \
		models/mx_model_update.c \
		models/mx_model_del.c \
		controllers/mx_signup.c \
		controllers/mx_signin.c \
		controllers/mx_gen_auth_token.c \
		controllers/mx_date_now.c \
		controllers/mx_date_aval.c \
		controllers/mx_contr_renew.c)


OBJ = main.o \
	  mx_sqlite.o \
	  mx_socket.o \
	  mx_printerr.o \
	  mx_event.o  \
	  mx_parse_json.o \
	  mx_model_insert.o \
	  mx_model_select.o \
	  mx_model_update.o \
	  mx_model_del.o \
	  mx_signup.o \
	  mx_signin.o \
	  mx_gen_auth_token.o \
	  mx_date_now.o \
	  mx_date_aval.o \
	  mx_contr_renew.o

CC = clang

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -g3 -fsanitize=address

all : install

install : json uchat

json:
	@make -C $(JSONF)

uchat : $(SRC) inc/header.h libmx/libmx.a json-c/libjson-c.a
	@$(CC) $(CFLAGS) -c $(SRC) $(foreach d, $(INC), -I $d)
	@$(CC) $(CFLAGS) $(OBJ) $(JSONF)/$(JSON_NAME) $(LIBMXF) -l sqlite3 -o $(APP_NAME)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"
	@mkdir -p $(OBJ_DIR)
	@mv $(OBJ) $(OBJ_DIR)
	@rm -rf ./*.c ./*.h
	@rm -rf $(OBJ_DIR)
	@printf "$(APP_NAME) \033[31;1minstalled\033[0m\n"

uninstall : clean
	@make uninstall -C $(JSONF)
	@rm -rf $(APP_NAME)
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

clean :

	@make clean -C $(JSONF)
	@rm -rf $(OBJ_DIR)
	@printf "$(OBJD)\t   \033[31;1mdeleted\033[0m\n"

reinstall : uninstall install
