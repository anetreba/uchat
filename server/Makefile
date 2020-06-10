NAME = server

HEADER = header.h \

FILES = main \
		mx_sqlite \
		mx_socket \
		mx_printerr \


INC_H = $(addprefix "inc/", $(HEADER))

ROOT_C = $(addsuffix ".c", $(FILES))

SRC = $(addprefix "src/", $(ROOT_C))

ROOT_O = $(addsuffix ".o", $(FILES))



CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic  #-g -fsanitize=address

all: install clean

install:
    @make install -sC src/json
	@cp $(SRC) .
	@cp $(INC_H) .
	@clang $(CFLAGS) -c $(ROOT_C)
	@clang $(CFLAGS) -ltermcap $(ROOT_O) -l sqlite3  -o $(NAME)
	@mkdir -p obj
	@cp $(ROOT_O) obj/
	@rm -rf $(ROOT_O)

uninstall: clean
	@rm -rf $(NAME)

clean:
	@rm -rf $(ROOT_O)
	@rm -rf $(ROOT_C)
	@rm -rf $(HEADER)
	@rm -rf obj

reinstall: uninstall install
