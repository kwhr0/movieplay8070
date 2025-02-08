AS = as8070
LD = ld8070
OBJS = crt0.o main.o file.o base.o
LIB = /opt/fcc/lib/8070/lib8070.a

all: a.out

a.out: $(OBJS) $(LIB)
	$(LD) -b -C1 -Z0xff00 -m a.map $^

.c.o:
	fcc -m8070 -S $<
	$(AS) -l $(<:.c=.lst) $(<:.c=.s)

.s.o:
	$(AS) -l $(<:s.=.lst) $<

crt0.o: crt0.asm
	$(AS) -l crt0.lst $<

clean:
	rm -f *.{lst,o,s} a.{map,out}

base.o: base.h types.h
file.o: file.h base.h types.h
main.o: file.h base.h types.h
