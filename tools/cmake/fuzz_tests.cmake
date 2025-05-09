file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/fuzz-corpora")

add_fuzz_test(add_message_str
  SOURCES "${PROJECT_SOURCE_DIR}/test/fuzz/add_message_str.cpp"
  CORPUS_NAME cstring
)

add_fuzz_test(stump_str
  SOURCES "${PROJECT_SOURCE_DIR}/test/fuzz/stump_str.cpp"
  CORPUS_NAME cstring
)

add_custom_target(fuzz
  DEPENDS ${STUMPLESS_FUZZ_TESTS}
)
