if(NOT LCOV)
    message(WARNING "lcov not found - target 'test.coverage' will be unavailable.")
    return()
endif()

coverage(coverage ${COW_INCLUDE_DIR} -R ^test.unit)
