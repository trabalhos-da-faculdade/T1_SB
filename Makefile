<<<<<<< HEAD
=======

# MAKEFILE DO TRABALHO

>>>>>>> 0346d03f2b3c5b77b9dcc644138a71109ff8db6c
#
# Makefile para Linux e macOS
#

SOURCE  = main.c lib/SOIL/image_DXT.c lib/SOIL/image_helper.c lib/SOIL/SOIL.c lib/SOIL/stb_image_aug.c
OBJECTS = $(SOURCE:.c=.o)

UNAME = `uname`

all: $(TARGET)
	-@make $(UNAME)

Darwin: $(OBJECTS)
<<<<<<< HEAD
	gcc $(OBJECTS) -Wno-deprecated -framework OpenGL -framework GLUT -framework Cocoa -lm -o transition
=======
	gcc $(OBJECTS) -Wno-deprecated 	-framework OpenGL -framework GLUT -framework Cocoa -lm -o transition
>>>>>>> 0346d03f2b3c5b77b9dcc644138a71109ff8db6c

Linux: $(OBJECTS)
	gcc $(OBJECTS) -lGL -lGLU -lglut -lm -o transition

clean:
	-@ rm -f $(OBJECTS) transition
