PLATFORM=linux
include Makefile.in.$(PLATFORM)

.PHONY: all exe doc clean realclean

exe: sph.x 
doc: main.pdf derivation.pdf
all: exe doc

# =======

sph.x: sph.o params.o state.o binhash.o interact.o leapfrog.o io_txt.o 
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

sph.o: sph.c params.h state.h binhash.h interact.h leapfrog.h io.h 

params.o: params.c params.h
state.o: state.c state.h binhash.h
binhash.o: binhash.c binhash.h state.h zmorton.h
interact.o: interact.c interact.h state.h params.h binhash.h
leapfrog.o: leapfrog.c leapfrog.h state.h params.h
io_txt.o: io_txt.c io.h

%.o: %.c
	$(CC) -c $(CFLAGS) $(OPTFLAGS) $<

# =======
main.pdf: main.tex codes.tex
derivation.pdf: derivation.tex check_derivation.tex

codes.tex: params.h state.h interact.c binhash.h zmorton.h binhash.c \
		leapfrog.c sph.c params.c io_txt.c 
	dsbweb -o $@ -c $^

check_derivation.tex: check_derivation.m
	dsbweb -o $@ -m $^

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

# =======
stripped:
	rm -rf strip
	mkdir -p strip
	for f in *.c ; do awk -f strip.awk $$f > strip/$$f; done
	for f in *.h ; do awk -f strip.awk $$f > strip/$$f; done
	cp Makefile* README.md strip
	cp check_derivation.m derivation.tex main.tex strip
	
# =======

clean:
	rm -f *~ *.o
	rm -f codes.tex check_derivation.tex
	rm -f main.log main.aux main.out main.toc
	rm -f derivation.log derivation.aux derivation.out

realclean: clean
	rm -f main.pdf derivation.pdf *.x run.out *.pov
