Para compilar o programa, usando o linux, basta executar o make onde:

DEPS = tp.h
OBJ = main.o tp.o
EXEC = tp1 //(nome do executável a ser criado)

Após o programa ser compilado, deve-se executar com um arquivo de texto adicional, informando os comandos a serem usados. Exemplo:

./tp1 arquivo.txt
