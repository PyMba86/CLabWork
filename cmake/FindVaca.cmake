# - Find the Vaca library
#
# This module defines
#  VACA_INCLUDE_DIR, where to find Vaca/Vaca.h, etc.
#  VACA_LIBRARY, the library to link against to use Vaca.
#  VACA_FOUND, If false, do not try to use Vaca.


FIND_PATH(VACA_INCLUDE_DIR Vaca/Vaca.h)

FIND_LIBRARY(VACA_LIBRARY NAMES vaca)

IF(VACA_INCLUDE_DIR AND VACA_LIBRARY)
   SET(VACA_FOUND TRUE)
   MESSAGE(STATUS "VACA FOUND")
else()
   SET(VACA_FOUND FALSE)
   MESSAGE(STATUS "VACA NOT FOUND")
ENDIF(VACA_INCLUDE_DIR AND VACA_LIBRARY)

