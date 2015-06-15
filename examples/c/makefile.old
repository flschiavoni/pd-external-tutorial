# where to find files
SRCDIR := ./src
OBJDIR := ./obj

SOURCES := $(wildcard $(SRCDIR)/*.c)

current:
	@echo Try make pd_linux, pd_nt, pd_irix5, or pd_darwin

clean: ; rm -f $(OBJDIR)/*.pd_linux $(OBJDIR)/*.o

# ----------------------- NT -----------------------

pd_nt: $(EXTNAME).dll

.SUFFIXES: .obj .dll

PDNTCFLAGS = /W3 /WX /DNT /DPD /nologo
VC="D:\Program Files\Microsoft Visual Studio\Vc98"

PDNTINCLUDE = /I. /I\tcl\include /I..\..\src /I$(VC)\include

PDNTLDIR = $(VC)\lib
PDNTLIB = $(PDNTLDIR)\libc.lib \
	$(PDNTLDIR)\oldnames.lib \
	$(PDNTLDIR)\kernel32.lib \
	..\..\bin\pd.lib 

.c.dll:
	cl $(PDNTCFLAGS) $(PDNTINCLUDE) /c $(SRCDIR)/$*.c
	link /dll /export:$*_setup $*.obj $(PDNTLIB)

# override explicitly for tilde objects like this:
dspobj~.dll: dspobj~.c; 
	cl $(PDNTCFLAGS) $(PDNTINCLUDE) /c $(SRCDIR)/$*.c
	link /dll /export:dspobj_tilde_setup $*.obj $(PDNTLIB)

# ----------------------- IRIX 5.x -----------------------

EXTENSION := pd_irix5
pd_linux: $(addprefix $(OBJDIR)/, $(addsuffix .pd_linux,$(basename $(notdir $(SOURCES)))))

.SUFFIXES: .pd_irix5

SGICFLAGS5 = -o32 -DPD -DUNIX -DIRIX -O2


SGIINCLUDE =  -I../../src/

.c.pd_irix5:
	cc $(SGICFLAGS5) $(SGIINCLUDE) -o $(OBJDIR)/$*.o -c $(SRCDIR)/$*.c
	ld -elf -shared -rdata_shared -o $(OBJDIR)/$*.pd_irix5 $(OBJDIR)/$*.o
	rm $(OBJDIR)/$*.o

# ----------------------- LINUX i386 -----------------------

EXTENSION := pd_linux
pd_linux: $(addprefix $(OBJDIR)/, $(addsuffix .pd_linux,$(basename $(notdir $(SOURCES)))))

.SUFFIXES: .pd_linux

LINUXCFLAGS = -DPD -O2 -fPIC -funroll-loops -fomit-frame-pointer \
    -Wall -W -Wshadow -Wstrict-prototypes -Werror \
    -Wno-unused -Wno-parentheses -Wno-switch

LINUXINCLUDE =  -Iinclude

$(OBJDIR)/%.$(EXTENSION): $(SRCDIR)/%.c
	cc $(LINUXCFLAGS) $(LINUXINCLUDE) -o $(OBJDIR)/$*.o -c $(SRCDIR)/$*.c
	ld -shared -o $(OBJDIR)/$*.pd_linux $(OBJDIR)/$*.o -lc -lm
	strip --strip-unneeded $(OBJDIR)/$*.pd_linux
	rm $(OBJDIR)/$*.o

# ----------------------- Mac OSX -----------------------

EXTENSION := pd_darwin
pd_linux: $(addprefix $(OBJDIR)/, $(addsuffix .pd_linux,$(basename $(notdir $(SOURCES)))))

.SUFFIXES: .pd_darwin

DARWINCFLAGS = -DPD -O2 -Wall -W -Wshadow -Wstrict-prototypes \
    -Wno-unused -Wno-parentheses -Wno-switch

$(OBJDIR)/%.$(EXTENSION): $(SRCDIR)/%.c
.c.pd_darwin:
	cc $(DARWINCFLAGS) $(LINUXINCLUDE) -o $(OBJDIR)/$*.o -c $(SRCDIR)/$*.c
	cc -bundle -undefined suppress -flat_namespace -o $(OBJDIR)/$*.pd_darwin $(OBJDIR)/$*.o 
	rm -f $(OBJDIR)/$*.o

