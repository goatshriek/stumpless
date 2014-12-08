!include <win32.mak>

INCDIR = $(BASEDIR)\include
SRCDIR = $(BASEDIR)\src
TESTDIR = $(BASEDIR)\test
OUTDIR = $(BASEDIR)\build

all: $(OUTDIR) $(OUTDIR)\stumpless.dll


# build output directories 
$(OUTDIR):
    if not exist "$(OUTDIR)\$(NULL)" mkdir $(OUTDIR)
    if not exist "$(OUTDIR)\src\$(NULL)" mkdir $(OUTDIR)\src
    if not exist "$(OUTDIR)\src\adapter\$(NULL)" mkdir $(OUTDIR)\src\adapter
    if not exist "$(OUTDIR)\src\comparator\$(NULL)" mkdir $(OUTDIR)\src\comparator
    if not exist "$(OUTDIR)\src\container\$(NULL)" mkdir $(OUTDIR)\src\container
    if not exist "$(OUTDIR)\src\container\dictionary\$(NULL)" mkdir $(OUTDIR)\src\container\dictionary
    if not exist "$(OUTDIR)\src\container\list\$(NULL)" mkdir $(OUTDIR)\src\container\list
    if not exist "$(OUTDIR)\src\container\list\const_iterator\$(NULL)" mkdir $(OUTDIR)\src\container\list\const_iterator
    if not exist "$(OUTDIR)\src\container\list\const_reverse_iterator\$(NULL)" mkdir $(OUTDIR)\src\container\list\const_reverse_iterator
    if not exist "$(OUTDIR)\src\container\list\iterator\$(NULL)" mkdir $(OUTDIR)\src\container\list\iterator
    if not exist "$(OUTDIR)\src\container\list\reverse_iterator\$(NULL)" mkdir $(OUTDIR)\src\container\list\reverse_iterator
    if not exist "$(OUTDIR)\src\filter\$(NULL)" mkdir $(OUTDIR)\src\filter
    if not exist "$(OUTDIR)\src\formatter\$(NULL)" mkdir $(OUTDIR)\src\formatter
    if not exist "$(OUTDIR)\src\handler\$(NULL)" mkdir $(OUTDIR)\src\handler
    if not exist "$(OUTDIR)\src\level\$(NULL)" mkdir $(OUTDIR)\src\level
    if not exist "$(OUTDIR)\src\logger\$(NULL)" mkdir $(OUTDIR)\src\logger
    if not exist "$(OUTDIR)\src\output\$(NULL)" mkdir $(OUTDIR)\src\output
    if not exist "$(OUTDIR)\src\private\$(NULL)" mkdir $(OUTDIR)\src\private
    if not exist "$(OUTDIR)\src\private\event\$(NULL)" mkdir $(OUTDIR)\src\private\event
    if not exist "$(OUTDIR)\src\status\$(NULL)" mkdir $(OUTDIR)\src\status
    if not exist "$(OUTDIR)\src\value\$(NULL)" mkdir $(OUTDIR)\src\value
    if not exist "$(OUTDIR)\test\function\$(NULL)" mkdir $(OUTDIR)\test\function
    if not exist "$(OUTDIR)\helper\$(NULL)" mkdir $(OUTDIR)\helper
    
    
# build library
$(OUTDIR)\stumpless.dll: $(OUTDIR)\src\adapter.obj \
                         $(OUTDIR)\src\adapter\base.obj \
                         $(OUTDIR)\src\adapter\initializer.obj \
                         $(OUTDIR)\src\boolean.obj \
                         $(OUTDIR)\src\comparator.obj \
                         $(OUTDIR)\src\comparator\base.obj \
                         $(OUTDIR)\src\comparator\initializer.obj \
                         $(OUTDIR)\src\configuration.obj \
                         $(OUTDIR)\src\container\dictionary.obj \
                         $(OUTDIR)\src\container\dictionary\const_iterator.obj \
                         $(OUTDIR)\src\container\list.obj \
                         $(OUTDIR)\src\container\list\adapter.obj \
                         $(OUTDIR)\src\container\list\comparator.obj \
                         $(OUTDIR)\src\container\list\const_iterator.obj \
                         $(OUTDIR)\src\container\list\const_iterator\adapter.obj \
                         $(OUTDIR)\src\container\list\const_iterator\comparator.obj \
                         $(OUTDIR)\src\container\list\const_iterator\filter.obj \
                         $(OUTDIR)\src\container\list\const_iterator\formatter.obj \
                         $(OUTDIR)\src\container\list\const_iterator\handler.obj \
                         $(OUTDIR)\src\container\list\const_iterator\target.obj \
                         $(OUTDIR)\src\container\list\const_iterator\value.obj \
                         $(OUTDIR)\src\container\list\const_reverse_iterator.obj \
                         $(OUTDIR)\src\container\list\const_reverse_iterator\adapter.obj \
                         $(OUTDIR)\src\container\list\const_reverse_iterator\comparator.obj \
                         $(OUTDIR)\src\container\list\const_reverse_iterator\filter.obj \
                         $(OUTDIR)\src\container\list\const_reverse_iterator\formatter.obj \
                         $(OUTDIR)\src\container\list\const_reverse_iterator\handler.obj \
                         $(OUTDIR)\src\container\list\const_reverse_iterator\target.obj \
                         $(OUTDIR)\src\container\list\const_reverse_iterator\value.obj \
                         $(OUTDIR)\src\container\list\filter.obj \
                         $(OUTDIR)\src\container\list\formatter.obj \
                         $(OUTDIR)\src\container\list\handler.obj \
                         $(OUTDIR)\src\container\list\iterator.obj \
                         $(OUTDIR)\src\container\list\iterator\adapter.obj \
                         $(OUTDIR)\src\container\list\iterator\comparator.obj \
                         $(OUTDIR)\src\container\list\iterator\filter.obj \
                         $(OUTDIR)\src\container\list\iterator\formatter.obj \
                         $(OUTDIR)\src\container\list\iterator\handler.obj \
                         $(OUTDIR)\src\container\list\iterator\target.obj \
                         $(OUTDIR)\src\container\list\iterator\value.obj \
                         $(OUTDIR)\src\container\list\reverse_iterator.obj \
                         $(OUTDIR)\src\container\list\reverse_iterator\adapter.obj \
                         $(OUTDIR)\src\container\list\reverse_iterator\comparator.obj \
                         $(OUTDIR)\src\container\list\reverse_iterator\filter.obj \
                         $(OUTDIR)\src\container\list\reverse_iterator\formatter.obj \
                         $(OUTDIR)\src\container\list\reverse_iterator\handler.obj \
                         $(OUTDIR)\src\container\list\reverse_iterator\target.obj \
                         $(OUTDIR)\src\container\list\reverse_iterator\value.obj \
                         $(OUTDIR)\src\container\list\target.obj \
                         $(OUTDIR)\src\container\list\value.obj \
                         $(OUTDIR)\src\container\queue.obj \
                         $(OUTDIR)\src\container\stack.obj \
                         $(OUTDIR)\src\container\tree.obj \
                         $(OUTDIR)\src\event.obj \
                         $(OUTDIR)\src\event_attribute.obj \
                         $(OUTDIR)\src\filter.obj \
                         $(OUTDIR)\src\filter\base.obj \
                         $(OUTDIR)\src\filter\initializer.obj \
                         $(OUTDIR)\src\formatter.obj \
                         $(OUTDIR)\src\formatter\csv.obj \
                         $(OUTDIR)\src\formatter\initializer.obj \
                         $(OUTDIR)\src\formatter\text.obj \
                         $(OUTDIR)\src\handler.obj \
                         $(OUTDIR)\src\handler\initializer.obj \
                         $(OUTDIR)\src\handler\stream.obj \
                         $(OUTDIR)\src\level.obj \
                         $(OUTDIR)\src\level\initializer.obj \
                         $(OUTDIR)\src\logger.obj \
                         $(OUTDIR)\src\logger\getter.obj \
                         $(OUTDIR)\src\logger\log.obj \
                         $(OUTDIR)\src\logger\sender.obj \
                         $(OUTDIR)\src\output.obj \
                         $(OUTDIR)\src\output\profile.obj \
                         $(OUTDIR)\src\output\profile_initializer.obj \
                         $(OUTDIR)\src\private\event\initializer.obj \
                         $(OUTDIR)\src\record.obj \
                         $(OUTDIR)\src\record_attribute.obj \
                         $(OUTDIR)\src\status.obj \
                         $(OUTDIR)\src\status\initializer.obj \
                         $(OUTDIR)\src\string_helper.obj \
                         $(OUTDIR)\src\target.obj \
                         $(OUTDIR)\src\value.obj \
                         $(OUTDIR)\src\value\constructor.obj \
                         $(OUTDIR)\src\value\profile.obj \
                         $(OUTDIR)\src\value\profile_initializer.obj
    $(link) $(linkdebug) $(dlllflags) -out:$(OUTDIR)\stumpless.dll /DEF:$(BASEDIR)\stumpless.def \
            $(OUTDIR)\src\adapter.obj \
            $(OUTDIR)\src\adapter\base.obj \
            $(OUTDIR)\src\adapter\initializer.obj \
            $(OUTDIR)\src\boolean.obj \
            $(OUTDIR)\src\comparator.obj \
            $(OUTDIR)\src\comparator\base.obj \
            $(OUTDIR)\src\comparator\initializer.obj \
            $(OUTDIR)\src\configuration.obj \
            $(OUTDIR)\src\container\dictionary.obj \
            $(OUTDIR)\src\container\dictionary\const_iterator.obj \
            $(OUTDIR)\src\container\list.obj \
            $(OUTDIR)\src\container\list\adapter.obj \
            $(OUTDIR)\src\container\list\comparator.obj \
            $(OUTDIR)\src\container\list\const_iterator.obj \
            $(OUTDIR)\src\container\list\const_iterator\adapter.obj \
            $(OUTDIR)\src\container\list\const_iterator\comparator.obj \
            $(OUTDIR)\src\container\list\const_iterator\filter.obj \
            $(OUTDIR)\src\container\list\const_iterator\formatter.obj \
            $(OUTDIR)\src\container\list\const_iterator\handler.obj \
            $(OUTDIR)\src\container\list\const_iterator\target.obj \
            $(OUTDIR)\src\container\list\const_iterator\value.obj \
            $(OUTDIR)\src\container\list\const_reverse_iterator.obj \
            $(OUTDIR)\src\container\list\const_reverse_iterator\adapter.obj \
            $(OUTDIR)\src\container\list\const_reverse_iterator\comparator.obj \
            $(OUTDIR)\src\container\list\const_reverse_iterator\filter.obj \
            $(OUTDIR)\src\container\list\const_reverse_iterator\formatter.obj \
            $(OUTDIR)\src\container\list\const_reverse_iterator\handler.obj \
            $(OUTDIR)\src\container\list\const_reverse_iterator\target.obj \
            $(OUTDIR)\src\container\list\const_reverse_iterator\value.obj \
            $(OUTDIR)\src\container\list\filter.obj \
            $(OUTDIR)\src\container\list\formatter.obj \
            $(OUTDIR)\src\container\list\handler.obj \
            $(OUTDIR)\src\container\list\iterator.obj \
            $(OUTDIR)\src\container\list\iterator\adapter.obj \
            $(OUTDIR)\src\container\list\iterator\comparator.obj \
            $(OUTDIR)\src\container\list\iterator\filter.obj \
            $(OUTDIR)\src\container\list\iterator\formatter.obj \
            $(OUTDIR)\src\container\list\iterator\handler.obj \
            $(OUTDIR)\src\container\list\iterator\target.obj \
            $(OUTDIR)\src\container\list\iterator\value.obj \
            $(OUTDIR)\src\container\list\reverse_iterator.obj \
            $(OUTDIR)\src\container\list\reverse_iterator\adapter.obj \
            $(OUTDIR)\src\container\list\reverse_iterator\comparator.obj \
            $(OUTDIR)\src\container\list\reverse_iterator\filter.obj \
            $(OUTDIR)\src\container\list\reverse_iterator\formatter.obj \
            $(OUTDIR)\src\container\list\reverse_iterator\handler.obj \
            $(OUTDIR)\src\container\list\reverse_iterator\target.obj \
            $(OUTDIR)\src\container\list\reverse_iterator\value.obj \
            $(OUTDIR)\src\container\list\target.obj \
            $(OUTDIR)\src\container\list\value.obj \
            $(OUTDIR)\src\container\queue.obj \
            $(OUTDIR)\src\container\stack.obj \
            $(OUTDIR)\src\container\tree.obj \
            $(OUTDIR)\src\event.obj \
            $(OUTDIR)\src\event_attribute.obj \
            $(OUTDIR)\src\filter.obj \
            $(OUTDIR)\src\filter\base.obj \
            $(OUTDIR)\src\filter\initializer.obj \
            $(OUTDIR)\src\formatter.obj \
            $(OUTDIR)\src\formatter\csv.obj \
            $(OUTDIR)\src\formatter\initializer.obj \
            $(OUTDIR)\src\formatter\text.obj \
            $(OUTDIR)\src\handler.obj \
            $(OUTDIR)\src\handler\initializer.obj \
            $(OUTDIR)\src\handler\stream.obj \
            $(OUTDIR)\src\level.obj \
            $(OUTDIR)\src\level\initializer.obj \
            $(OUTDIR)\src\logger.obj \
            $(OUTDIR)\src\logger\getter.obj \
            $(OUTDIR)\src\logger\log.obj \
            $(OUTDIR)\src\logger\sender.obj \
            $(OUTDIR)\src\output.obj \
            $(OUTDIR)\src\output\profile.obj \
            $(OUTDIR)\src\output\profile_initializer.obj \
            $(OUTDIR)\src\private\event\initializer.obj \
            $(OUTDIR)\src\record.obj \
            $(OUTDIR)\src\record_attribute.obj \
            $(OUTDIR)\src\status.obj \
            $(OUTDIR)\src\status\initializer.obj \
            $(OUTDIR)\src\string_helper.obj \
            $(OUTDIR)\src\target.obj \
            $(OUTDIR)\src\value.obj \
            $(OUTDIR)\src\value\constructor.obj \
            $(OUTDIR)\src\value\profile.obj \
            $(OUTDIR)\src\value\profile_initializer.obj
    

# library object files
$(OUTDIR)\src\adapter.obj: $(OUTDIR) $(SRCDIR)\adapter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\adapter.c
    
$(OUTDIR)\src\adapter\base.obj: $(SRCDIR)\adapter\base.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\adapter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\adapter\base.c
    
$(OUTDIR)\src\adapter\initializer.obj: $(SRCDIR)\adapter\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\adapter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\adapter\initializer.c
    
$(OUTDIR)\src\boolean.obj: $(SRCDIR)\boolean.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\boolean.c
    
$(OUTDIR)\src\comparator.obj: $(SRCDIR)\comparator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\comparator.c
    
$(OUTDIR)\src\comparator\base.obj: $(SRCDIR)\comparator\base.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\comparator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\comparator\base.c
    
$(OUTDIR)\src\comparator\initializer.obj: $(SRCDIR)\comparator\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\comparator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\comparator\initializer.c
    
$(OUTDIR)\src\configuration.obj: $(SRCDIR)\configuration.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\configuration.c
    
$(OUTDIR)\src\container\dictionary.obj: $(SRCDIR)\container\dictionary.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\dictionary.c
    
$(OUTDIR)\src\container\dictionary\const_iterator.obj: $(SRCDIR)\container\dictionary\const_iterator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\dictionary\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\dictionary\const_iterator.c
    
$(OUTDIR)\src\container\list.obj: $(SRCDIR)\container\list.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list.c
    
$(OUTDIR)\src\container\list\adapter.obj: $(SRCDIR)\container\list\adapter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\adapter.c
    
$(OUTDIR)\src\container\list\comparator.obj: $(SRCDIR)\container\list\comparator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\comparator.c
    
$(OUTDIR)\src\container\list\const_iterator.obj: $(SRCDIR)\container\list\const_iterator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator.c
    
$(OUTDIR)\src\container\list\const_iterator\adapter.obj: $(SRCDIR)\container\list\const_iterator\adapter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\adapter.c
    
$(OUTDIR)\src\container\list\const_iterator\comparator.obj: $(SRCDIR)\container\list\const_iterator\comparator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\comparator.c
    
$(OUTDIR)\src\container\list\const_iterator\filter.obj: $(SRCDIR)\container\list\const_iterator\filter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\filter.c
    
$(OUTDIR)\src\container\list\const_iterator\formatter.obj: $(SRCDIR)\container\list\const_iterator\formatter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\formatter.c
    
$(OUTDIR)\src\container\list\const_iterator\handler.obj: $(SRCDIR)\container\list\const_iterator\handler.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\handler.c
    
$(OUTDIR)\src\container\list\const_iterator\target.obj: $(SRCDIR)\container\list\const_iterator\target.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\target.c
    
$(OUTDIR)\src\container\list\const_iterator\value.obj: $(SRCDIR)\container\list\const_iterator\value.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_iterator\value.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator.obj: $(SRCDIR)\container\list\const_reverse_iterator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\adapter.obj: $(SRCDIR)\container\list\const_reverse_iterator\adapter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\adapter.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\comparator.obj: $(SRCDIR)\container\list\const_reverse_iterator\comparator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\comparator.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\filter.obj: $(SRCDIR)\container\list\const_reverse_iterator\filter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\filter.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\formatter.obj: $(SRCDIR)\container\list\const_reverse_iterator\formatter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\formatter.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\handler.obj: $(SRCDIR)\container\list\const_reverse_iterator\handler.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\handler.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\target.obj: $(SRCDIR)\container\list\const_reverse_iterator\target.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\target.c
    
$(OUTDIR)\src\container\list\const_reverse_iterator\value.obj: $(SRCDIR)\container\list\const_reverse_iterator\value.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\const_reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\const_reverse_iterator\value.c
    
$(OUTDIR)\src\container\list\filter.obj: $(SRCDIR)\container\list\filter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\filter.c
    
$(OUTDIR)\src\container\list\formatter.obj: $(SRCDIR)\container\list\formatter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\formatter.c
    
$(OUTDIR)\src\container\list\handler.obj: $(SRCDIR)\container\list\handler.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\handler.c
    
$(OUTDIR)\src\container\list\iterator.obj: $(SRCDIR)\container\list\iterator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator.c
    
$(OUTDIR)\src\container\list\iterator\adapter.obj: $(SRCDIR)\container\list\iterator\adapter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\adapter.c
    
$(OUTDIR)\src\container\list\iterator\comparator.obj: $(SRCDIR)\container\list\iterator\comparator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\comparator.c
    
$(OUTDIR)\src\container\list\iterator\filter.obj: $(SRCDIR)\container\list\iterator\filter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\filter.c
    
$(OUTDIR)\src\container\list\iterator\formatter.obj: $(SRCDIR)\container\list\iterator\formatter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\formatter.c
    
$(OUTDIR)\src\container\list\iterator\handler.obj: $(SRCDIR)\container\list\iterator\handler.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\handler.c
    
$(OUTDIR)\src\container\list\iterator\target.obj: $(SRCDIR)\container\list\iterator\target.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\target.c
    
$(OUTDIR)\src\container\list\iterator\value.obj: $(SRCDIR)\container\list\iterator\value.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\iterator\value.c
    
$(OUTDIR)\src\container\list\reverse_iterator.obj: $(SRCDIR)\container\list\reverse_iterator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator.c
    
$(OUTDIR)\src\container\list\reverse_iterator\adapter.obj: $(SRCDIR)\container\list\reverse_iterator\adapter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\adapter.c
    
$(OUTDIR)\src\container\list\reverse_iterator\comparator.obj: $(SRCDIR)\container\list\reverse_iterator\comparator.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\comparator.c
    
$(OUTDIR)\src\container\list\reverse_iterator\filter.obj: $(SRCDIR)\container\list\reverse_iterator\filter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\filter.c
    
$(OUTDIR)\src\container\list\reverse_iterator\formatter.obj: $(SRCDIR)\container\list\reverse_iterator\formatter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\formatter.c
    
$(OUTDIR)\src\container\list\reverse_iterator\handler.obj: $(SRCDIR)\container\list\reverse_iterator\handler.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\handler.c
    
$(OUTDIR)\src\container\list\reverse_iterator\target.obj: $(SRCDIR)\container\list\reverse_iterator\target.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\target.c
    
$(OUTDIR)\src\container\list\reverse_iterator\value.obj: $(SRCDIR)\container\list\reverse_iterator\value.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\reverse_iterator\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\reverse_iterator\value.c
    
$(OUTDIR)\src\container\list\target.obj: $(SRCDIR)\container\list\target.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\target.c
    
$(OUTDIR)\src\container\list\value.obj: $(SRCDIR)\container\list\value.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\list\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\list\value.c
    
$(OUTDIR)\src\container\queue.obj: $(SRCDIR)\container\queue.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\queue.c
    
$(OUTDIR)\src\container\stack.obj: $(SRCDIR)\container\stack.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\stack.c
    
$(OUTDIR)\src\container\tree.obj: $(SRCDIR)\container\tree.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\container\ /Fd$(OUTDIR)\src\ $(SRCDIR)\container\tree.c
    
$(OUTDIR)\src\event.obj: $(SRCDIR)\event.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\event.c
    
$(OUTDIR)\src\event_attribute.obj: $(SRCDIR)\event_attribute.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\event_attribute.c
    
$(OUTDIR)\src\filter.obj: $(SRCDIR)\filter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\filter.c
    
$(OUTDIR)\src\filter\base.obj: $(SRCDIR)\filter\base.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\filter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\filter\base.c
    
$(OUTDIR)\src\filter\initializer.obj: $(SRCDIR)\filter\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\filter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\filter\initializer.c
    
$(OUTDIR)\src\formatter.obj: $(SRCDIR)\formatter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\formatter.c
    
$(OUTDIR)\src\formatter\csv.obj: $(SRCDIR)\formatter\csv.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\formatter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\formatter\csv.c
    
$(OUTDIR)\src\formatter\initializer.obj: $(SRCDIR)\formatter\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\formatter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\formatter\initializer.c
    
$(OUTDIR)\src\formatter\text.obj: $(SRCDIR)\formatter\text.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\formatter\ /Fd$(OUTDIR)\src\ $(SRCDIR)\formatter\text.c
    
$(OUTDIR)\src\handler.obj: $(SRCDIR)\handler.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\handler.c
    
$(OUTDIR)\src\handler\initializer.obj: $(SRCDIR)\handler\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\handler\ /Fd$(OUTDIR)\src\ $(SRCDIR)\handler\initializer.c
    
$(OUTDIR)\src\handler\stream.obj: $(SRCDIR)\handler\stream.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\handler\ /Fd$(OUTDIR)\src\ $(SRCDIR)\handler\stream.c
    
$(OUTDIR)\src\level.obj: $(SRCDIR)\level.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\level.c
    
$(OUTDIR)\src\level\initializer.obj: $(SRCDIR)\level\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\level\ /Fd$(OUTDIR)\src\ $(SRCDIR)\level\initializer.c
    
$(OUTDIR)\src\logger.obj: $(SRCDIR)\logger.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\logger.c
    
$(OUTDIR)\src\logger\getter.obj: $(SRCDIR)\logger\getter.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\logger\ /Fd$(OUTDIR)\src\ $(SRCDIR)\logger\getter.c
    
$(OUTDIR)\src\logger\log.obj: $(SRCDIR)\logger\log.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\logger\ /Fd$(OUTDIR)\src\ $(SRCDIR)\logger\log.c
    
$(OUTDIR)\src\logger\sender.obj: $(SRCDIR)\logger\sender.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\logger\ /Fd$(OUTDIR)\src\ $(SRCDIR)\logger\sender.c
    
$(OUTDIR)\src\output.obj: $(SRCDIR)\output.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\output.c
    
$(OUTDIR)\src\output\profile.obj: $(SRCDIR)\output\profile.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\output\ /Fd$(OUTDIR)\src\ $(SRCDIR)\output\profile.c
    
$(OUTDIR)\src\output\profile_initializer.obj: $(SRCDIR)\output\profile_initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\output\ /Fd$(OUTDIR)\src\ $(SRCDIR)\output\profile_initializer.c
    
$(OUTDIR)\src\private\event\initializer.obj: $(SRCDIR)\private\event\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\private\event\ /Fd$(OUTDIR)\src\ $(SRCDIR)\private\event\initializer.c
    
$(OUTDIR)\src\record.obj: $(SRCDIR)\record.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\record.c
    
$(OUTDIR)\src\record_attribute.obj: $(SRCDIR)\record_attribute.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\record_attribute.c
    
$(OUTDIR)\src\status.obj: $(SRCDIR)\status.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\status.c
    
$(OUTDIR)\src\status\initializer.obj: $(SRCDIR)\status\initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\status\ /Fd$(OUTDIR)\src\ $(SRCDIR)\status\initializer.c
    
$(OUTDIR)\src\string_helper.obj: $(SRCDIR)\string_helper.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\string_helper.c
    
$(OUTDIR)\src\target.obj: $(SRCDIR)\target.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\target.c
    
$(OUTDIR)\src\value.obj: $(SRCDIR)\value.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\ /Fd$(OUTDIR)\src\ $(SRCDIR)\value.c
    
$(OUTDIR)\src\value\constructor.obj: $(SRCDIR)\value\constructor.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\value\ /Fd$(OUTDIR)\src\ $(SRCDIR)\value\constructor.c
    
$(OUTDIR)\src\value\profile.obj: $(SRCDIR)\value\profile.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\value\ /Fd$(OUTDIR)\src\ $(SRCDIR)\value\profile.c
    
$(OUTDIR)\src\value\profile_initializer.obj: $(SRCDIR)\value\profile_initializer.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\src\value\ /Fd$(OUTDIR)\src\ $(SRCDIR)\value\profile_initializer.c
    

# run tests
check: $(OUTDIR)\stumpless.dll $(OUTDIR)\test\function\adapter.exe $(OUTDIR)\test\function\boolean.exe $(OUTDIR)\test\function\configuration.exe
    - $(OUTDIR)\test\function\adapter.exe >> $(OUTDIR)\test-suite.log
    if errorlevel 1 echo "Adapter Test Failed"
    - $(OUTDIR)\test\function\boolean.exe >> $(OUTDIR)\test-suite.log
    if errorlevel 1 echo "Boolean Test Failed"
    - $(OUTDIR)\test\function\configuration.exe >> $(OUTDIR)\test-suite.log
    if errorlevel 1 echo "Configuration Test Failed"


# executable files
$(OUTDIR)\test\function\adapter.exe: $(OUTDIR)\test\function\adapter.obj $(OUTDIR)\helper\builder.obj  $(OUTDIR)\helper\fixture.obj $(OUTDIR)\helper\log.obj
    $(link) $(linkdebug) -out:$(OUTDIR)\test\function\adapter.exe $(OUTDIR)\test\function\adapter.obj $(OUTDIR)\helper\builder.obj $(OUTDIR)\helper\fixture.obj $(OUTDIR)\helper\log.obj $(OUTDIR)\stumpless.lib
    
$(OUTDIR)\test\function\boolean.exe: $(OUTDIR)\test\function\boolean.obj $(OUTDIR)\helper\builder.obj  $(OUTDIR)\helper\fixture.obj $(OUTDIR)\helper\log.obj
    $(link) $(linkdebug) -out:$(OUTDIR)\test\function\boolean.exe $(OUTDIR)\test\function\boolean.obj $(OUTDIR)\helper\builder.obj $(OUTDIR)\helper\fixture.obj $(OUTDIR)\helper\log.obj $(OUTDIR)\stumpless.lib
    
$(OUTDIR)\test\function\configuration.exe: $(OUTDIR)\test\function\configuration.obj $(OUTDIR)\helper\builder.obj  $(OUTDIR)\helper\fixture.obj $(OUTDIR)\helper\log.obj
    $(link) $(linkdebug) -out:$(OUTDIR)\test\function\configuration.exe $(OUTDIR)\test\function\configuration.obj $(OUTDIR)\helper\builder.obj $(OUTDIR)\helper\fixture.obj $(OUTDIR)\helper\log.obj $(OUTDIR)\stumpless.lib
    
    
# test object files
$(OUTDIR)\test\function\adapter.obj: $(TESTDIR)\function\adapter.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\adapter.c
    
$(OUTDIR)\test\function\boolean.obj: $(TESTDIR)\function\boolean.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\boolean.c
    
$(OUTDIR)\test\function\configuration.obj: $(TESTDIR)\function\configuration.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\test\function\ /Fd$(OUTDIR)\test\function\ $(TESTDIR)\function\configuration.c


# helper library object files
$(OUTDIR)\helper\builder.obj: $(TESTDIR)\helper\builder.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\helper\ /Fd$(OUTDIR)\helper\ $(TESTDIR)\helper\builder.c

$(OUTDIR)\helper\fixture.obj: $(TESTDIR)\helper\fixture.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\helper\ /Fd$(OUTDIR)\helper\ $(TESTDIR)\helper\fixture.c

$(OUTDIR)\helper\log.obj: $(TESTDIR)\helper\log.c
    $(cc) $(cflags) $(cdebug) /I $(INCDIR) /Fo$(OUTDIR)\helper\ /Fd$(OUTDIR)\helper\ $(TESTDIR)\helper\log.c
    
    
clean:
    $(CLEANUP)