function(include_file source_filename include_filenames already_included)
  foreach(include_filename ${include_filenames})
    file(APPEND "${source_filename}" "\n/* ${include_filename} */\n\n")
    file(STRINGS "${include_filename}" raw_include_contents NEWLINE_CONSUME ENCODING UTF-8)
    string(REPLACE "\;" "@SEMICOLON@" sanitized_include_contents "${raw_include_contents}")
    string(REPLACE "[" "@OPEN_BRACKET@" sanitized_include_contents "${sanitized_include_contents}")
    string(REPLACE "]" "@CLOSE_BRACKET@" sanitized_include_contents "${sanitized_include_contents}")
    string(REPLACE "\n" ";" file_lines "${sanitized_include_contents}")
    foreach(line ${file_lines})
      if("${line}" MATCHES ".*include .((private|stumpless)/.+\.h).$")
        if("${CMAKE_MATCH_1}" STREQUAL "private/config.h")
          set(extracted_full_path "${PROJECT_BINARY_DIR}/include/private/config.h")
        elseif("${CMAKE_MATCH_1}" STREQUAL "stumpless/config.h")
          set(extracted_full_path "${PROJECT_BINARY_DIR}/include/stumpless/config.h")
        elseif("${CMAKE_MATCH_1}" STREQUAL "stumpless/windows/default_events.h")
          set(extracted_full_path "${PROJECT_BINARY_DIR}/include/stumpless/windows/default_events.h")
        else()
          set(extracted_full_path "${PROJECT_SOURCE_DIR}/include/${CMAKE_MATCH_1}")
        endif()
        list(FIND ${already_included} "${extracted_full_path}" FOUND_INDEX)
        if(${FOUND_INDEX} EQUAL -1 AND EXISTS "${extracted_full_path}")
          list(APPEND ${already_included} "${extracted_full_path}")
          include_file(
            "${source_filename}"
            "${extracted_full_path}"
            ${already_included}
          )
        endif()
      else()
        set(prev_line "")
        foreach(subline ${line})
          if(NOT prev_line STREQUAL "")
            file(APPEND "${source_filename}" "${prev_line}\\\n")
          endif()
          string(REPLACE "@CLOSE_BRACKET@" "]" original_subline "${subline}")
          string(REPLACE "@OPEN_BRACKET@" "[" original_subline "${original_subline}")
          string(REPLACE "@SEMICOLON@" ";" original_subline "${original_subline}")
          set(prev_line "${original_subline}")
        endforeach()
        file(APPEND "${source_filename}" "${prev_line}\n")
      endif()
    endforeach()
  endforeach()
endfunction()

message("creating single file library ${SINGLE_SOURCE_FILE}")
file(WRITE "${SINGLE_SOURCE_FILE}" "")
set(include_list "")
foreach(source_file ${STUMPLESS_SOURCES})
  if("${source_file}" MATCHES "\\.c$")
    include_file(
      "${SINGLE_SOURCE_FILE}"
      "${source_file}"
      include_list
    )
  endif()
endforeach()

message("creating single header ${SINGLE_HEADER_FILE}")
file(WRITE "${SINGLE_HEADER_FILE}" "")
set(include_list "")
include_file(
  "${SINGLE_HEADER_FILE}"
  "${PROJECT_SOURCE_DIR}/include/stumpless.h"
  include_list
)

# this needs to happen after the stumpless library is set up
get_property(STUMPLESS_LINK_LIBRARIES TARGET stumpless PROPERTY LINK_LIBRARIES)
foreach(single_file_target ${STUMPLESS_SINGLE_FILE_TARGETS})
  target_link_libraries(${single_file_target} ${STUMPLESS_LINK_LIBRARIES})
endforeach()

add_custom_target(bench-single-file
  DEPENDS ${STUMPLESS_BENCH_SINGLE_FILE_RUNNERS}
)

add_custom_target(check-single-file
  DEPENDS ${STUMPLESS_CHECK_SINGLE_FILE_RUNNERS}
)

add_custom_target(examples-single-file
  DEPENDS ${STUMPLESS_EXAMPLE_SINGLE_FILE_RUNNERS}
)
