!include <win32.mak>

INCDIR = C:\Users\Joel\code\stumpless-c\include
SRCDIR = C:\Users\Joel\code\stumpless-c\test
OUTDIR = C:\Users\Joel\code\stumpless-c\build\test
LIBDIR = C:\Users\Joel\code\stumpless-c\build

all: $(OUTDIR) $(SRCDIR)\function\adapter.exe

$(OUTDIR):
    if not exist "$(OUTDIR)\$(NULL)" mkdir $(OUTDIR)
    if not exist "$(OUTDIR)\function\$(NULL)" mkdir $(OUTDIR)\function
    if not exist "$(OUTDIR)\helper\$(NULL)" mkdir $(OUTDIR)\helper


# object files

$(OUTDIR)\function\adapter.obj: $(SRCDIR)\function\adapter.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\function\ /Fd$(OUTDIR)\function\ $(SRCDIR)\function\adapter.c

$(OUTDIR)\helper\builder.obj: $(SRCDIR)\helper\builder.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\helper\ /Fd$(OUTDIR)\helper\ $(SRCDIR)\helper\builder.c

$(OUTDIR)\helper\fixture.obj: $(SRCDIR)\helper\fixture.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\helper\ /Fd$(OUTDIR)\helper\ $(SRCDIR)\helper\fixture.c

$(OUTDIR)\helper\log.obj: $(SRCDIR)\helper\log.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\helper\ /Fd$(OUTDIR)\helper\ $(SRCDIR)\helper\log.c


# executable files

$(SRCDIR)\function\adapter.exe: $(OUTDIR)\function\adapter.obj $(OUTDIR)\helper\builder.obj  $(OUTDIR)\helper\fixture.obj $(OUTDIR)\helper\log.obj
    $(link) $(linkdebug) -out:$(OUTDIR)\function\adapter.exe $(OUTDIR)\function\adapter.obj $(OUTDIR)\helper\builder.obj $(OUTDIR)\helper\fixture.obj $(OUTDIR)\helper\log.obj $(LIBDIR)\stumpless.lib
    
clean:
    $(CLEANUP)