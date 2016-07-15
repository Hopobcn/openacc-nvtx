CC     = pgcc
CFLAGS = -fPIC -ta=tesla -I$(CUDA_HOME)/include -I$(ACC_HOME)/include
LFLAGS = -L$(CUDA_HOME)/lib64 -lnvToolsExt
AR=ar

liboaccnvtx.so: liboaccnvtx.a
	$(CC) -shared -o $@ $(LFLAGS) -lnvToolsExt -Wl,-soname=$@ -Wl,--whole-archive $< -Wl,--no-whole-archive

openacc-nvtx.o: openacc-nvtx.c
	$(CC) $(CFLAGS) -c $<

liboaccnvtx.a: openacc-nvtx.o
	$(AR) cr $@ $^

.PHONY: clean realclean
clean: 
	rm -rf *.o core

realclean: clean
	rm -rf *.so *.a
