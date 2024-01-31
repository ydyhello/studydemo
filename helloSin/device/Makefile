MT3k_ENV=/vol8/appsoftware/mt3000_programming_env-inbox/mt3000_programming_env-20230315
ENV_ROOT=${MT3k_ENV}/hthreads
GCCROOT=${MT3k_ENV}/dsp_compiler
MT_LIBVM=/vol8/home/hnu_ydy/libvm_expr/libvm_mt_public

CC=MT-3000-gcc
AR=MT-3000-ar
LD=MT-3000-ld
AS=MT-3000-as
OB=MT-3000-objdump
DAT=MT-3000-makedat

export LD_LIBRARY_PATH=/vol8/appsoftware/mt3000_programming_env-inbox/mt3000_programming_env-20230315/third-party-lib/:$LD_LIBRARY_PATH

CFLAGS=-c -O2 -g -gdwarf-2 -fenable-m3000 -ffunction-sections -flax-vector-conversions -I./ -I$(ENV_ROOT)/include -I$(GCCROOT)/include/
LDFLAGS= -L$(ENV_ROOT)/lib --gc-sections -Tdsp.lds

SRC=helloSin.dev.c
OBJ=helloSin.dev.o
EXE=helloSin.dev.out
DAT=helloSin.dev.dat

ALL: $(EXE)
	$(GCCROOT)/bin/MT-3000-makedat -J $(EXE)


$(OBJ): $(SRC)
	$(GCCROOT)/bin/$(CC) -I$(MT_LIBVM)/include $(CFLAGS) $(SRC) -o $(OBJ) 

$(EXE): $(OBJ)
	$(GCCROOT)/bin/$(LD) $(LDFLAGS) $(OBJ) $(MT_LIBVM)/lib/libvm.a $(ENV_ROOT)/lib/libhthread_device.a $(GCCROOT)/lib/vlib3000.a $(GCCROOT)/lib/slib3000.a -o $(EXE) 

clean:
	rm $(EXE) $(OBJ) $(DAT)
