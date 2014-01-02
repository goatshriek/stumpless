AM_CFLAGS = -g -I $(top_srcdir)/include -I ./include

lib_LTLIBRARIES = libstumpless.la

libstumpless_la_SOURCES = src/adapter.c \
                          src/adapter_base.c \
                          src/adapter_initializer.c \
                          src/boolean.c \
                          src/compare_base.c \
                          src/configuration.c \
                          src/csv_formatter.c \
                          src/dictionary.c \
                          src/entry.c \
                          src/event.c \
                          src/filter.c \
                          src/filter_base.c \
                          src/filter_initializer.c \
                          src/formatter.c \
                          src/formatter_initializer.c \
                          src/formatter_list.c \
                          src/handler.c \
                          src/handler_initializer.c \
                          src/level.c \
                          src/list.c \
                          src/list_iterator.c \
                          src/logger.c \
                          src/output.c \
                          src/output_profile.c \
                          src/output_profile_initializer.c \
                          src/stack.c \
                          src/status.c \
                          src/status_initializer.c \
                          src/stream_handler.c \
                          src/string_helper.c \
                          src/text_formatter.c \
                          src/tree.c \
                          src/value.c \
                          src/value_constructor.c \
                          src/value_profile.c \
                          src/value_profile_initializer.c

include src/list/Makefile.am
include src/wrapper/Makefile.am
