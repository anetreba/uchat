NAME	=	libjson-c.a

#CFLG	=	-std=c11 $(addprefix -W, all extra error pedantic)
CFLG	=	-std=c11 $(addprefix -W, all)

SRCD	=	./
INCD	=	./
OBJD	=	obj

INC		=   arraylist.h \
            config.h.win32 \
            debug.h \
            json.h \
            json_c_version.h \
            json_config.h.in \
            json_config.h.win32 \
            json_inttypes.h \
            json_object.h \
            json_object_iterator.h \
            json_object_private.h \
            json_pointer.h \
            json_tokener.h \
            json_types.h \
            json_util.h \
            json_visit.h \
            linkhash.h \
            math_compat.h \
            printbuf.h \
            random_seed.h \
            snprintf_compat.h \
            strdup_compat.h \
            strerror_override.h \
            strerror_override_private.h \
            vasprintf_compat.h

INCS	=	$(addprefix $(INCD)/, $(INC))

SRC     =   arraylist.c \
            debug.c \
            json_c_version.c \
            json_object.c \
            json_object_iterator.c \
            json_pointer.c \
            json_tokener.c \
            json_util.c \
            json_visit.c \
            libjson.c \
            linkhash.c \
            printbuf.c \
            random_seed.c \
            strerror_override.c

SRCS	=	$(addprefix $(SRCD)/, $(SRC))
OBJS	=	$(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: install

install: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@clang $(CFLG) -c $< -o $@ -I$(INCD)
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRCD)/%.c=%) "

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@


clean:
	@rm -rf $(OBJD)
	@printf "$(OBJD)\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@rm -rf $(NAME)
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install