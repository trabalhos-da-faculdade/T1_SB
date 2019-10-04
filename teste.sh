#!/bin/bash

gcc main.c lib/SOIL/*.c -lm -lGL -lGLU -lglut -o run
./run blue.png mr_robot.png mr_robot_universe.png
