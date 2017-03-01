CC = gcc
SRC = dsp_design.c
BINDIR = bin
CFLAGS = -std=c11 -Ofast -lm -march=native -mtune=native

default: dsp_design_double

prepare:
	mkdir -p $(BINDIR)

dsp_design_float: prepare
	$(CC) $(SRC) $(CFLAGS) -lfftw3f -DFLOAT_PRECISION=0 -o $(BINDIR)/$@

dsp_design_double: prepare
	$(CC) $(SRC) $(CFLAGS) -lfftw3 -DFLOAT_PRECISION=1 -o $(BINDIR)/$@

dsp_design_longdouble: prepare
	$(CC) $(SRC) $(CFLAGS) -lfftw3l -DFLOAT_PRECISION=2 -o $(BINDIR)/$@

dsp_design_float128: prepare
	$(CC) $(SRC) $(CFLAGS) -lfftw3q -lquadmath -DFLOAT_PRECISION=3 -o $(BINDIR)/$@

clean:
	rm -f $(BINDIR)/*
