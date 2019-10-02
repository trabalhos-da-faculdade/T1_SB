#!/bin/bash

gcc main.c lib/SOIL/*.c -lm -lGL -lGLU -lglut -o run
./run mr_robot.png
