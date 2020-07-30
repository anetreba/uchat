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
      		controllers/mx_select_listroom_and_mess.c \
      		controllers/mx_contr_select_contacts.c \
      		controllers/mx_contr_add_room.c \
      		controllers/mx_contr_logout.c \
      		controllers/encrypt.c \
      		crud/mx_model_del.c \
      		crud/mx_model_insert.c \
      		crud/mx_model_select.c \
      		crud/mx_model_update.c \
      		models/mx_model_logined.c \
      		models/mx_model_new_message.c \
      		models/mx_model_add_contact.c \
      		models/mx_model_update_contacts.c \
      		models/mx_model_new_room.c \
      		mx_list_room_mess.c \
      		mx_add_new_mess.c \
      		mx_add_new_room.c \
      		mx_client_recv.c \
      		mx_init_chat_window.c \
      		mx_renew_contact.c \
      		mx_parse_cont.c \
      		mx_add_cont_show.c \
      		mx_event.c \
      		db/mx_db_creation.c \
      		db/mx_create_table.c \
      		db/mx_table_contacts.c \
      		db/mx_table_messages.c \
      		db/mx_table_rooms.c \
      		db/mx_table_settings.c)


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
      mx_list_room_mess.o \
      mx_add_new_mess.o \
      mx_add_new_room.o \
      mx_client_recv.o \
      mx_init_chat_window.o \
      mx_contr_renew_contacts.o \
      mx_model_update_contacts.o \
      mx_contr_add_contact.o \
      mx_model_add_contact.o \
      mx_contr_select_contacts.o \
      mx_renew_contact.o \
      mx_parse_cont.o \
      mx_add_cont_show.o \
      mx_contr_add_room.o \
      mx_model_new_room.o \
      mx_contr_logout.o \
      encrypt.o \
      mx_db_creation.o \
      mx_create_table.o \
      mx_table_contacts.o \
      mx_table_messages.o \
      mx_table_rooms.o \
      mx_table_settings.o


CC = clang

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic #-g3 -fsanitize=address

CL_GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`
CL_GTK_SORT_FLAGS = `pkg-config --cflags gtk+-3.0`

all : install

install : json uchat

json:
	@make -C $(JSONF)

uchat : $(SRC) inc/header.h libmx/libmx.a json-c/libjson-c.a
	@$(CC) $(CFLAGS) -c $(SRC) $(foreach d, $(INC), -I $d) $(CL_GTK_SORT_FLAGS) -I/usr/local/opt/openssl/include
	@$(CC) $(CFLAGS) $(OBJ) $(CL_GTK_FLAGS) $(JSONF)/$(JSON_NAME) $(LIBMXF) -L/usr/local/opt/openssl/lib -lssl -lcrypto -l sqlite3 -o $(APP_NAME)
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
