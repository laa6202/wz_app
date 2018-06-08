#CC=arm-linux-gcc
CC=gcc 
FLAG= -std=c99
LIB=
INCDIR=inc -I ../inc
OUTDIR=out
TAR=mSEED
SRC=main.c action_mseed.c \
		buf4mseed.c	btime.c
#		cmd_op.c	\
#		cspi_rw.c pspi_read.c key_read.c\
#		wzpkg.c \
#		dir_save.c send_to_net.c
OBJ=main.o action_mseed.o  \
		buf4mseed.o	btime.o
#		cmd_op.o \
#		cspi_rw.o pspi_read.o key_read.o\
#		wzpkg.o \
#		dir_save.o send_to_net.o

$(TAR) : $(OBJ)
	$(CC) -o $@ $^

$(OBJ) : $(SRC)
	$(CC) $(FLAG) -c $^ -I $(INCDIR)

clean : 
	rm -rf $(TAR) $(OBJ)

