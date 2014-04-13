AM_CFLAGS = -g -I $(top_srcdir)/include -I ./include

lib_LTLIBRARIES = libstumpless.la

libstumpless_la_SOURCES = src/adapter.c \
                          src/adapter_base.c \
                          src/adapter_initializer.c \
                          src/boolean.c \
                          src/comparator.c \
                          src/comparator_base.c \
                          src/comparator_initializer.c \
                          src/configuration.c \
                          src/dictionary.c \
                          src/entry.c \
                          src/entry_attribute.c \
                          src/event.c \
                          src/event_attribute.c \
                          src/filter.c \
                          src/filter_base.c \
                          src/filter_initializer.c \
                          src/formatter.c \
                          src/handler.c \
                          src/handler_initializer.c \
                          src/level.c \
                          src/list.c \
                          src/logger.c \
                          src/output.c \
                          src/output_profile.c \
                          src/output_profile_initializer.c \
                          src/stack.c \
                          src/status.c \
                          src/status_initializer.c \
                          src/stream_handler.c \
                          src/string_helper.c \
                          src/tree.c \
                          src/value.c \
                          src/value_constructor.c \
                          src/value_profile.c \
                          src/value_profile_initializer.c

include src/formatter/Makefile.am
include src/list/Makefile.am
include src/wrapper/Makefile.am
