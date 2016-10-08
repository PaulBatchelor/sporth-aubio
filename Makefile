aubio_onset.so: aubio_onset.c
	$(CC) -shared -fPIC $^ -o $@ -lsoundpipe -lsporth -lm -ldl -lpthread -ljack

clean:
	rm -rf *.so
