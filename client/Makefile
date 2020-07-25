APP_NAME = uchat

LIBMXF = libmx/libmx.a

JSONF = json-c

JSON_NAME = libjson-c.a

INC = inc/ \
	  json-c/

SRC_DIR = src

OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/,\
      		main.c \
      		mx_printerr.c \
      		mx_parse_json.c \
      		mx_sqlite.c\
      		controllers/mx_contr_auth.c \
      		controllers/mx_contr_renew.c\
      		controllers/mx_contr_update_rooms.c \
      		controllers/mx_contr_new_message.c \
      		controllers/mx_contr_renew_contacts.c \
      		controllers/mx_contr_add_contact.c \
      		crud/mx_model_del.c \
      		crud/mx_model_insert.c \
      		crud/mx_model_select.c \
      		crud/mx_model_update.c \
      		models/mx_model_logined.c \
      		models/mx_model_new_message.c \
      		models/mx_model_add_contact.c \
      		controllers/mx_select_listroom_and_mess.c \
      		models/mx_model_update_contacts.c \
      		mx_event.c)


OBJ = main.o \
      mx_printerr.o \
      mx_parse_json.o \
      mx_model_del.o \
      mx_model_insert.o \
      mx_model_select.o \
      mx_model_update.o \
      mx_sqlite.o \
      mx_model_logined.o \
      mx_contr_auth.o \
      mx_contr_renew.o \
      mx_event.o \
      mx_contr_update_rooms.o \
      mx_contr_new_message.o \
      mx_model_new_message.o \
      mx_select_listroom_and_mess.o \
      mx_contr_renew_contacts.o \
      mx_model_update_contacts.o \
      mx_contr_add_contact.o \
      mx_model_add_contact.o

CC = clang

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic #-g3 -fsanitize=address

CL_GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`
CL_GTK_SORT_FLAGS = `pkg-config --cflags gtk+-3.0`

all : install

install : json uchat

json:
	@make -C $(JSONF)

uchat : $(SRC) inc/header.h libmx/libmx.a json-c/libjson-c.a
	@$(CC) $(CFLAGS) -c $(SRC) $(foreach d, $(INC), -I $d) $(CL_GTK_SORT_FLAGS)
	@$(CC) $(CFLAGS) $(OBJ) $(CL_GTK_FLAGS) $(JSONF)/$(JSON_NAME) $(LIBMXF) -l sqlite3 -o $(APP_NAME)
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
