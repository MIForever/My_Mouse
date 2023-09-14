TARGET = my_mouse
SRC = *.c src/*.c
CFLAGS = -Wall -Wextra -Werror -g3

$(TARGET): $(SRC)
	gcc $(CFLAGS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -f ${TARGET}