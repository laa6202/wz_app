#CC=arm-linux-gcc
CC=gcc 
FLAG= -std=c99
TAR=wz_app
SRC=main.c init.c action.c \
		config_analyze.c	\
		cmd_op.c	\
		cspi_rw.c pspi_read.c \
		dir_save.c
OBJ=main.o init.o action.o \
		config_analyze.o			\
		cmd_op.o \
		cspi_rw.o pspi_read.o \
		dir_save.o
LIB=
INC=

$(TAR) : $(OBJ)
	$(CC) -o $@ $^

$(OBJ) : $(SRC)
	$(CC) $(FLAG) -c $^

clean : 
	rm -rf $(TAR) $(OBJ)

