# Make sure libaubio.a is in this directory

LDFLAGS= -lsoundpipe -lsporth -lm -ldl -lpthread -ljack libaubio.a

aubio_onset.so: aubio_onset.c
	$(CC) -shared -fPIC $^ -o $@ $(LDFLAGS)

clean:
	rm -rf *.so
