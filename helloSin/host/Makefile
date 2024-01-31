MT3k_ENV=/vol8/appsoftware/mt3000_programming_env-inbox/mt3000_programming_env-20230315
ENV_ROOT=${MT3k_ENV}/hthreads
MT_LIBVM=/vol8/home/hnu_ydy/libvm_expr/libvm_mt_public

EXE=helloSin.hos

ALL:
	gcc -O2 ${EXE}.c -std=c99 -I./ -I$(ENV_ROOT)/include -I$(MT_LIBVM)/include -I$(MT_LIBVM)/lib $(ENV_ROOT)/lib/libhthread_host.a -lpthread -fopenmp -lm -o ${EXE}
	

clean:
	rm ${EXE}