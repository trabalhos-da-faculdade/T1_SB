#!/bin/bash

# ----------------------
#  TESTANDO O PROGRAMA
# ---------------------

# Limpando a utilização do make
make clean

# Compilando de novo 
make

# Mostrando todas as Imagens Possiveis
echo " "
echo " "
echo " SELECIONE A IMAGEM DESEJADA "
echo " "
echo "---------------------------------------"
ls *.png
echo "---------------------------------------"
echo " "

# Selecione a Imagem Desejada
echo " Digite a Imagem que deseja modificar: ";
read image1;

echo " Digite a Imagem que deseja pegar as cores: ";
read image2;

./transition ${image1}.png ${image2}.png


