#### CMakeLists.txt PcaServo ####

# Specifies the sources for this module with optional sources included by platform
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/PcaServo.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PcaServo.fpp"
)


# Specifies any module dependencies not detectable via the model file dependency detection
#set(MOD_DEPS ...)

# Registers this module with the fprime build system
register_fprime_module()

# Specifies the sources specifically associated with unit tests in this module
set(UT_SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/TesterBase.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/GTestBase.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/main.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PcaServo.fpp"
)


# Specifies any unit test modules
#set(UT_MOD_DEPS ...)

# Registers this module with the fprime build system
register_fprime_ut()
