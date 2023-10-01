message("creating single file library ${SINGLE_SOURCE_FILE}")

function(include_file source_filename include_filenames already_included)
  foreach(include_filename ${include_filenames})
    file(APPEND "${source_filename}" "\n/* ${include_filename} */\n\n")
    file(STRINGS "${include_filename}" raw_include_contents NEWLINE_CONSUME ENCODING UTF-8)
    string(REPLACE "\;" "@SEMICOLON@" sanitized_include_contents "${raw_include_contents}")
    string(REPLACE "[" "@OPEN_BRACKET@" sanitized_include_contents "${sanitized_include_contents}")
    string(REPLACE "]" "@CLOSE_BRACKET@" sanitized_include_contents "${sanitized_include_contents}")
    string(REPLACE "\n" ";" file_lines "${sanitized_include_contents}")
    foreach(line ${file_lines})
      if("${line}" MATCHES ".*include \"(private/.+\.h)\"$")
        if("${CMAKE_MATCH_1}" STREQUAL "private/config.h")
          set(extracted_full_path "${PROJECT_BINARY_DIR}/include/private/config.h")
        else()
          set(extracted_full_path "${PROJECT_SOURCE_DIR}/include/${CMAKE_MATCH_1}")
        endif()
        list(FIND ${already_included} "${extracted_full_path}" FOUND_INDEX)
        if(${FOUND_INDEX} EQUAL -1)
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

# this needs to happen after the stumpless library is set up
get_target_property(STUMPLESS_LINK_LIBRARIES stumpless LINK_LIBRARIES)
foreach(example_target ${STUMPLESS_SINGLE_FILE_TARGETS})
  target_link_libraries(${example_target} ${STUMPLESS_LINK_LIBRARIES})
endforeach()

add_custom_target(check-single-file
  DEPENDS ${STUMPLESS_CHECK_SINGLE_FILE_RUNNERS}
)

add_custom_target(examples-single-file
  DEPENDS ${STUMPLESS_EXAMPLE_SINGLE_FILE_RUNNERS}
)
