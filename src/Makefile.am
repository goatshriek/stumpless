AM_CFLAGS = -g -I $(top_srcdir)/include -I ./include

lib_LTLIBRARIES = libstumpless.la

libstumpless_la_SOURCES = src/adapter.c \
                          src/boolean.c \
                          src/comparator.c \
                          src/configuration.c \
                          src/event.c \
                          src/event_attribute.c \
                          src/exception.c \
                          src/filter.c \
                          src/formatter.c \
                          src/handler.c \
                          src/level.c \
                          src/logger.c \
                          src/output.c \
                          src/record.c \
                          src/record_attribute.c \
                          src/string_helper.c \
                          src/target.c \
                          src/value.c

include src/adapter/Makefile.am
include src/comparator/Makefile.am
include src/container/Makefile.am
include src/filter/Makefile.am
include src/formatter/Makefile.am
include src/handler/Makefile.am
include src/level/Makefile.am
include src/logger/Makefile.am
include src/output/Makefile.am
include src/private/Makefile.am
include src/value/Makefile.am
