check_PROGRAMS = test/function/adapter_suite \
                 test/function/boolean_suite \
                 test/function/comparator_suite \
                 test/function/comparator/base_suite \
                 test/function/configuration_suite \
                 test/function/event_suite \
                 test/function/exception_suite \
                 test/function/exception/handler_suite \
                 test/function/exception/initializer_suite \
                 test/function/exception/thrower_suite \
                 test/function/filter_suite \
                 test/function/filter/base_suite \
                 test/function/level_suite \
                 test/function/logger_suite \
                 test/function/logger/log_suite \
                 test/function/output_suite \
                 test/function/output/profile_suite \
                 test/function/output/profile_initializer_suite \
                 test/function/record_suite \
                 test/function/record_attribute_suite \
                 test/function/string_helper_suite \
                 test/function/target_suite \
                 test/function/value_suite \
                 test/function/value/constructor_suite \
                 test/function/value/profile_suite \
                 test/function/value/profile_initializer_suite \
                 test/function/container/dictionary_suite \
                 test/function/container/dictionary/const_iterator_suite \
                 test/function/container/list_suite \
                 test/function/container/list/adapter_suite \
                 test/function/container/list/comparator_suite \
				         test/function/container/list/const_iterator_suite \
                 test/function/container/list/filter_suite \
                 test/function/container/list/formatter_suite \
                 test/function/container/list/handler_suite \
                 test/function/container/list/iterator_suite \
                 test/function/container/list/reverse_iterator_suite \
                 test/function/container/list/value_suite \
                 test/function/container/queue_suite \
                 test/function/container/stack_suite \
                 test/function/container/tree_suite \
                 test/function/formatter_suite \
                 test/function/formatter/text_suite \
                 test/function/handler_suite \
                 test/function/handler/stream_suite

TESTS = $(check_PROGRAMS)

test_libraries = libhelper.la \
                 libstumpless.la

include test/helper/Makefile.am
include test/function/Makefile.am
