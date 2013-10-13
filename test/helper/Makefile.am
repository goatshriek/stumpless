check_LTLIBRARIES = libhelper.la

libhelper_la_SOURCES = test/helper/builder.c \
                       test/include/builder.h \
                       test/include/checker.h \
                       test/include/helper.h \
                       test/include/runner.h
libhelper_la_CFLAGS = $(AM_CFLAGS) -I $(top_srcdir)/test/include
libhelper_la_LIBADD = libstumpless.la
