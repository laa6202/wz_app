#CC=arm-linux-gcc
CC=gcc
TAR=wz_app
SRC=main.c init.c action.c \
		config_analyze.c	\
		cspi_rw.c pspi_read.c \
		send_DS7.c 
OBJ=main.o init.o action.o \
		config_analyze.o			\
		cspi_rw.o pspi_read.o \
		send_DS7.o
LIB=
INC=

$(TAR) : $(OBJ)
	$(CC) -o $@ $^

$(OBJ) : $(SRC)
	$(CC) -c $^

clean : 
	rm -rf $(TAR) $(OBJ)

