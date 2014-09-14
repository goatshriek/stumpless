check_PROGRAMS = test/function/adapter \
                 test/function/boolean \
                 test/function/comparator/base \
                 test/function/comparator/main \
                 test/function/configuration \
                 test/function/event \
                 test/function/filter/base \
                 test/function/filter/main \
                 test/function/level \
                 test/function/logger \
                 test/function/output/main \
                 test/function/output/profile \
                 test/function/output/profile_initializer \
                 test/function/record \
                 test/function/record_attribute \
                 test/function/status/initializer \
                 test/function/status/main \
                 test/function/string_helper \
                 test/function/target \
                 test/function/value/constructor \
                 test/function/value/main \
                 test/function/value/profile \
                 test/function/value/profile_initializer \
                 test/function/container/dictionary \
                 test/function/container/stack \
                 test/function/container/tree \
                 test/function/container/list/adapter \
                 test/function/container/list/comparator \
                 test/function/container/list/event_attribute \
                 test/function/container/list/filter \
                 test/function/container/list/formatter \
                 test/function/container/list/handler \
                 test/function/container/list/main \
                 test/function/container/list/record_attribute \
                 test/function/container/list/value \
                 test/function/container/list/iterator/iterator \
                 test/function/container/list/reverse_iterator/reverse_iterator \
                 test/function/formatter/main \
                 test/function/formatter/text \
                 test/function/handler/main \
                 test/function/handler/stream

TESTS = $(check_PROGRAMS)

test_flags = $(AM_CFLAGS) -I $(top_srcdir)/test/include
test_libraries = libhelper.la \
                 libstumpless.la

include test/helper/Makefile.am
include test/function/Makefile.am
