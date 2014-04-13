check_PROGRAMS = test/function/adapter \
                 test/function/boolean \
                 test/function/comparator_base \
                 test/function/configuration \
                 test/function/dictionary \
                 test/function/entry \
                 test/function/event \
                 test/function/filter \
                 test/function/filter_base \
                 test/function/formatter \
                 test/function/handler \
                 test/function/level \
                 test/function/logger \
                 test/function/output \
                 test/function/output_profile \
                 test/function/output_profile_initializer \
                 test/function/stack \
                 test/function/status \
                 test/function/status_initializer \
                 test/function/stream_handler \
                 test/function/string_helper \
                 test/function/text_formatter \
                 test/function/tree \
                 test/function/value \
                 test/function/value_constructor \
                 test/function/value_profile \
                 test/function/value_profile_initializer \
                 test/function/list/adapter \
                 test/function/list/comparator \
                 test/function/list/entry_attribute \
                 test/function/list/event_attribute \
                 test/function/list/filter \
                 test/function/list/formatter \
                 test/function/list/handler \
                 test/function/list/list \
                 test/function/list/value \
                 test/function/list/iterator/iterator
TESTS = $(check_PROGRAMS)

test_flags = $(AM_CFLAGS) -I $(top_srcdir)/test/include
test_libraries = libhelper.la \
                 libstumpless.la

include test/helper/Makefile.am
include test/function/Makefile.am
