#GCCROOT=/home/zp/mt3000_programming_env/dsp_compiler
#ENV_ROOT=/home/zp/mt3000_programming_env/hthreads
GCCROOT=/vol8/appsoftware/mt3000_programming_env/dsp_compiler
ENV_ROOT=/vol8/appsoftware/mt3000_programming_env/hthreads
CC=MT-3000-gcc
AR=MT-3000-ar
LD=MT-3000-ld

#export LD_LIBRARY_PATH=/home/zp/mt3000_programming_env/third-party-lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/vol8/appsoftware/mt3000_programming_env/third-party-lib:$LD_LIBRARY_PATH
CFLAGS=-c -O2 -g -gdwarf-2 -fenable-m3000 -ffunction-sections -flax-vector-conversions -I./ -I$(ENV_ROOT)/include -I$(GCCROOT)/include/
LDFLAGS= -L$(ENV_ROOT)/lib --gc-sections -Tdsp.lds
SRC=add_kernel.c
OBJ=add_kernel.o
EXE=add_kernel.out
DAT=add_kernel.dat




ALL: $(EXE)
	$(GCCROOT)/bin/MT-3000-makedat -J $(EXE)
	cp $(DAT) ../bin

$(OBJ): $(SRC)
	$(GCCROOT)/bin/$(CC) $(CFLAGS) $(SRC) -o $(OBJ) 

$(EXE): $(OBJ)
	$(GCCROOT)/bin/$(LD) $(LDFLAGS) $(OBJ) $(ENV_ROOT)/lib/libhthread_device.a $(GCCROOT)/lib/vlib3000.a $(GCCROOT)/lib/slib3000.a -o $(EXE) 

clean:
	rm $(EXE) $(OBJ) $(DAT)
