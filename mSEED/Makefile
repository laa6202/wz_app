#CC=arm-linux-gcc
CC=gcc 
FLAG= -std=c99
LIB=
INCDIR=inc -I ../inc
OUTDIR=out
TAR=mSEED
SRC=main.c action_mseed.c \
		buf4mseed.c	btime.c file_op.c \
		gen_mseed.c gen_par.c \
		alg_steim2.c alg_head.c
#		cspi_rw.c pspi_read.c key_read.c\
#		wzpkg.c \
#		dir_save.c send_to_net.c
OBJ=main.o action_mseed.o  \
		buf4mseed.o	btime.o file_op.o \
		gen_mseed.o	gen_par.o \
		alg_steim2.o alg_head.o
#		cspi_rw.o pspi_read.o key_read.o\
#		wzpkg.o \
#		dir_save.o send_to_net.o

$(TAR) : $(OBJ)
	$(CC) -o $@ $^

$(OBJ) : $(SRC)
	$(CC) $(FLAG) -c $^ -I $(INCDIR)

clean : 
	rm -rf $(TAR) $(OBJ)

