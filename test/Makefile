!include <win32.mak>

SRCDIR = C:\Users\Joel\code\stumpless-c\test
OUTDIR = C:\Users\Joel\code\stumpless-c\build\test

all: $(OUTDIR) $(SRCDIR)\function\adapter.exe

$(OUTDIR):
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(SRCDIR)\function\adapter.obj: $(SRCDIR)\function\adapter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SRCDIR)\function\adapter.c

$(SRCDIR)\function\adapter.exe: $(SRCDIR)\function\adapter.obj
    $(link) $(linkdebug) $(guiflags) -out:$(OUTDIR)\function\adapter.exe $(OUTDIR)\function\adapter.obj $(OUTDIR)\stumpless.lib
    
clean:
    $(CLEANUP)