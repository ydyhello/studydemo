

# ENV_ROOT=/home/zp/mt3000_programming_env/hthreads
ENV_ROOT=/vol8/appsoftware/mt3000_programming_env/hthreads

EXE=add_host

ALL:
	gcc -O2 ${EXE}.c -std=c99 -I./ -I$(ENV_ROOT)/include $(ENV_ROOT)/lib/libhthread_host.a -lpthread -fopenmp -o ${EXE}
	cp ${EXE} ../bin/

clean:
	rm ${EXE}
