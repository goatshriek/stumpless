!include <win32.mak>

INCDIR = C:\Users\Joel\code\stumpless-c\include
SRCDIR = C:\Users\Joel\code\stumpless-c\test
OUTDIR = C:\Users\Joel\code\stumpless-c\build\test
LIBDIR = C:\Users\Joel\code\stumpless-c\build

all: $(OUTDIR) $(SRCDIR)\function\adapter.exe

$(OUTDIR):
    if not exist "$(OUTDIR)\$(NULL)" mkdir $(OUTDIR)
    if not exist "$(OUTDIR)\function\$(NULL)" mkdir $(OUTDIR)\function

$(SRCDIR)\function\adapter.obj: $(SRCDIR)\function\adapter.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\function\ /Fd$(OUTDIR)\function\ $(SRCDIR)\function\adapter.c

$(SRCDIR)\function\adapter.exe: $(SRCDIR)\function\adapter.obj $(OUTDIR)\helper.obj
    $(link) $(linkdebug) -out:$(OUTDIR)\function\adapter.exe $(OUTDIR)\function\adapter.obj $(OUTDIR)\helper.obj $(LIBDIR)\stumpless.lib

$(OUTDIR)\helper.obj: $(SRCDIR)\helper\builder.c $(SRCDIR)\helper\fixture.c $(SRCDIR)\helper\log.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\ /Fd$(OUTDIR)\ $(SRCDIR)\helper\builder.c $(SRCDIR)\helper\fixture.c $(SRCDIR)\helper\log.c
    
clean:
    $(CLEANUP)