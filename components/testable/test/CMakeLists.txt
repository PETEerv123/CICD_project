set(src "Test_SPI.c")
set(include "include")
idf_component_register(SRCS "${src}"
                       INCLUDE_DIRS "${include}"
                       REQUIRES testable unity)