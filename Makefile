CC=gcc
TARGET=handy
OBJECTS=handy.o handy-window.o handy-popover.o
CFLAGS=-Wall -O2 `pkg-config --cflags glib-2.0 gtk+-3.0 vte-2.91 keybinder-3.0`
LDFLAGS=-Wall -O2
LIBS=`pkg-config --libs glib-2.0 gtk+-3.0 vte-2.91 keybinder-3.0`

all:	$(TARGET)
clean:
	rm -f $(OBJECTS) $(TARGET)
again:	clean all
$(TARGET):	$(OBJECTS)
	gcc -o $(TARGET) $(OBJECTS) $(LIBS)
.c.o:
	gcc -c $< -o $@ $(CFLAGS)
