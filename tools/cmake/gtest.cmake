set(GTEST_URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip) # v1.17.0
if(CMAKE_VERSION VERSION_LESS "3.24")
  # FIND_PACKAGE_ARGS is not available before 3.24, but for now we don't require
  # the higher version just for it
  FetchContent_Declare(
    googletest
    URL ${GTEST_URL}
  )
else()
  FetchContent_Declare(
    googletest
    URL ${GTEST_URL}
    FIND_PACKAGE_ARGS NAMES GTest
  )
endif()

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
