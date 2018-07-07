CC=arm-linux-gcc
#CC=gcc 
FLAG= -std=c99
LIB= -lpthread
INCDIR=inc -I mSEED/inc
OUTDIR=out
TAR=wz_app
SRC=main.c init.c action.c \
		config_analyze.c	\
		cmd_op.c	\
		cspi_rw.c pspi_read.c key_read.c\
		wzpkg.c \
		dir_save.c send_to_net.c \
		mSEED/action_mseed.c mSEED/alg_head.c mSEED/alg_steim2.c \
		mSEED/btime.c mSEED/buf4mseed.c mSEED/file_op.c \
		mSEED/gen_mseed.c mSEED/gen_par.c
OBJ=main.o init.o action.o \
		config_analyze.o			\
		cmd_op.o \
		cspi_rw.o pspi_read.o key_read.o\
		wzpkg.o \
		dir_save.o send_to_net.o \
		action_mseed.o alg_head.o alg_steim2.o \
		btime.o buf4mseed.o file_op.o \
		gen_mseed.o gen_par.o

$(TAR) : $(OBJ)
	$(CC) -o $@ $^ $(LIB)

$(OBJ) : $(SRC)
	$(CC) $(FLAG) -c $^ -I $(INCDIR)

clean : 
	rm -rf $(TAR) $(OBJ)

