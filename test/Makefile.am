check_PROGRAMS = test/function/adapter \
                 test/function/boolean \
                 test/function/comparator \
                 test/function/comparator_base \
                 test/function/configuration \
                 test/function/entry \
                 test/function/entry_attribute \
                 test/function/event \
                 test/function/filter \
                 test/function/filter_base \
                 test/function/level \
                 test/function/logger \
                 test/function/output \
                 test/function/output_profile \
                 test/function/output_profile_initializer \
                 test/function/status \
                 test/function/status_initializer \
                 test/function/string_helper \
                 test/function/value \
                 test/function/value_constructor \
                 test/function/value_profile \
                 test/function/value_profile_initializer \
                 test/function/container/dictionary \
                 test/function/container/stack \
                 test/function/container/tree \
                 test/function/container/list/adapter \
                 test/function/container/list/comparator \
                 test/function/container/list/entry_attribute \
                 test/function/container/list/event_attribute \
                 test/function/container/list/filter \
                 test/function/container/list/formatter \
                 test/function/container/list/handler \
                 test/function/container/list/list \
                 test/function/container/list/value \
                 test/function/container/list/iterator/iterator \
                 test/function/container/list/reverse_iterator/reverse_iterator \
                 test/function/formatter/formatter \
                 test/function/formatter/text \
                 test/function/handler/handler \
                 test/function/handler/stream

TESTS = $(check_PROGRAMS)

test_flags = $(AM_CFLAGS) -I $(top_srcdir)/test/include
test_libraries = libhelper.la \
                 libstumpless.la

include test/helper/Makefile.am
include test/function/Makefile.am
