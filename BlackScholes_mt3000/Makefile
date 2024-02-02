include Makefile.in
#
.PHONY: ALL
ALL:bsKernel

####
bsKernel.dev.o:bsKernel.dev.c
	$(DEV_CC) -c $(DEV_CFLAGS) -I$(LIBVM_ROOT_PATH)/include $^ -o $@

bsKernel.dev.out:bsKernel.dev.o
	$(DEV_LD) $^ $(DEV_LDFLAGS) $(LIBVM_ROOT_PATH)/lib/libvm.a -o $@ 

bsKernel.dev.dat:bsKernel.dev.out
	$(DEV_MAKEDAT) -J $^

####
BlackScholes_gold_mt3000.cpp.o:BlackScholes_gold_mt3000.cpp
	g++ ${HOS_CXXFLAGS} -o $@ -c $^
main_mt3000.cpp.o:main_mt3000.cpp
	g++ ${HOS_CXXFLAGS} -o $@ -c $^

BlackScholes_mt3000:main_mt3000.cpp.o BlackScholes_gold_mt3000.cpp.o
	g++  -o $@ $^ -march=armv8-a ${HOS_LDFLAGS}

bsKernel:BlackScholes_mt3000 bsKernel.dev.dat

####
.PHONY:clean
clean:
	rm -rf *.o *.out *.dat BlackScholes_mt3000
