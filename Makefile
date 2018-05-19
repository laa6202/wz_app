CC=arm-linux-gcc
#CC=gcc 
FLAG= -std=c99
LIB=
INCDIR=inc
OUTDIR=out
TAR=wz_app
SRC=main.c init.c action.c \
		config_analyze.c	\
		cmd_op.c	\
		cspi_rw.c pspi_read.c key_read.c\
		wzpkg.c \
		dir_save.c send_to_net.c
OBJ=main.o init.o action.o \
		config_analyze.o			\
		cmd_op.o \
		cspi_rw.o pspi_read.o key_read.o\
		wzpkg.o \
		dir_save.o send_to_net.o

$(TAR) : $(OBJ)
	$(CC) -o $@ $^

$(OBJ) : $(SRC)
	$(CC) $(FLAG) -c $^ -I $(INCDIR)

clean : 
	rm -rf $(TAR) $(OBJ)

