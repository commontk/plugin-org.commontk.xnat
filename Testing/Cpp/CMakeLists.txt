include_directories(
  ${org_commontk_xnat_SOURCE_DIR}
  )

create_test_sourcelist(ctkXnatTests_SRC
  ctkXnatTests.cpp
  ctkXnatConnectionTest.cpp
  )

add_definitions(-D_CRT_SECURE_NO_DEPRECATE)

set(ctkXnatTest_MOC_SRCS
  ctkXnatConnectionTest.h
  )

qt4_wrap_cpp(ctkXnatTest_MOC_OUTPUT ${ctkXnatTest_MOC_SRCS})

ADD_EXECUTABLE(ctkXnatTests ${ctkXnatTests_SRC} ${ctkXnatTest_MOC_OUTPUT})
TARGET_LINK_LIBRARIES(ctkXnatTests org_commontk_xnat qRestAPI)

MACRO(SIMPLE_TEST TESTNAME)
  ADD_TEST(NAME ${TESTNAME} COMMAND ctkXnatTests ${TESTNAME})
ENDMACRO()

SIMPLE_TEST(testXnatConnection)
