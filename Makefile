.POSIX:

include config.mk

SRC = weekday.c
OBJ = $(SRC:.c=.o)

all: options weekday

options:
	@echo 'weekday build options:'
	@echo "CFLAGS      = $(CFLAGS)"
	@echo "DEBUGFLAGS  = $(DEBUGFLAGS)"
	@echo "CC          = $(CC)"

$(OBJ): config.mk

weekday: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

debug: $(OBJ)
	$(CC) -o weekday-$@ $(OBJ) $(LDFLAGS) $(DEBUGDLAGS)

clean:
	rm -f weekday weekday-debug $(OBJ)

install: all
	mkdir -p $(PREFIX)/bin
	cp -f weekday $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin

uninstall:
	rm -f $(PREFIX)/bin/weekday

.PHONY: all options weekday debug clean install uninstall
