#!/bin/bash

gcc main.c lib/SOIL/*.c -lm -lGL -lGLU -lglut -o run
./run universe.png mr_robot.png mr_robot.png
