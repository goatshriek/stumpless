!include <win32.mak>

INCDIR = C:\Users\Joel\code\stumpless-c\include
SRCDIR = C:\Users\Joel\code\stumpless-c\test
OUTDIR = C:\Users\Joel\code\stumpless-c\build\test
LIBDIR = C:\Users\Joel\code\stumpless-c\build

all: $(OUTDIR) check


# build output directories 
$(OUTDIR):
    if not exist "$(OUTDIR)\$(NULL)" mkdir $(OUTDIR)
    if not exist "$(OUTDIR)\function\$(NULL)" mkdir $(OUTDIR)\function
    if not exist "$(OUTDIR)\helper\$(NULL)" mkdir $(OUTDIR)\helper
    
    
# run tests
check: $(OUTDIR)\function\adapter.exe $(OUTDIR)\function\boolean.exe
    $(OUTDIR)\function\adapter.exe >> $(OUTDIR)\test-suite.log
    if errorlevel 1 echo "Adapter Test Failed"
    $(OUTDIR)\function\boolean.exe >> $(OUTDIR)\test-suite.log
    if errorlevel 1 echo "Boolean Test Failed"


# executable files
$(OUTDIR)\function\adapter.exe: $(OUTDIR)\function\adapter.obj $(OUTDIR)\helper\builder.obj  $(OUTDIR)\helper\fixture.obj $(OUTDIR)\helper\log.obj
    $(link) $(linkdebug) -out:$(OUTDIR)\function\adapter.exe $(OUTDIR)\function\adapter.obj $(OUTDIR)\helper\builder.obj $(OUTDIR)\helper\fixture.obj $(OUTDIR)\helper\log.obj $(LIBDIR)\stumpless.lib
    
$(OUTDIR)\function\boolean.exe: $(OUTDIR)\function\boolean.obj $(OUTDIR)\helper\builder.obj  $(OUTDIR)\helper\fixture.obj $(OUTDIR)\helper\log.obj
    $(link) $(linkdebug) -out:$(OUTDIR)\function\boolean.exe $(OUTDIR)\function\boolean.obj $(OUTDIR)\helper\builder.obj $(OUTDIR)\helper\fixture.obj $(OUTDIR)\helper\log.obj $(LIBDIR)\stumpless.lib
    
    


# test object files
$(OUTDIR)\function\adapter.obj: $(SRCDIR)\function\adapter.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\function\ /Fd$(OUTDIR)\function\ $(SRCDIR)\function\adapter.c
    
$(OUTDIR)\function\boolean.obj: $(SRCDIR)\function\boolean.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\function\ /Fd$(OUTDIR)\function\ $(SRCDIR)\function\boolean.c


# helper library object files
$(OUTDIR)\helper\builder.obj: $(SRCDIR)\helper\builder.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\helper\ /Fd$(OUTDIR)\helper\ $(SRCDIR)\helper\builder.c

$(OUTDIR)\helper\fixture.obj: $(SRCDIR)\helper\fixture.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\helper\ /Fd$(OUTDIR)\helper\ $(SRCDIR)\helper\fixture.c

$(OUTDIR)\helper\log.obj: $(SRCDIR)\helper\log.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\helper\ /Fd$(OUTDIR)\helper\ $(SRCDIR)\helper\log.c
    
    
clean:
    $(CLEANUP)