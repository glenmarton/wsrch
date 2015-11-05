#Set this to @ to keep the makefile quiet
SILENCE = @
CPPUTEST_EXE_FLAGS = -c # Add color to command line prompt.

#---- Outputs ----#
COMPONENT_NAME = wsrch

#Set this to @ to keep the makefile quiet
SILENCE = @

#--- Inputs ----#
PROJECT_HOME_DIR = .
ifeq "$(CPPUTEST_HOME)" ""
    CPPUTEST_HOME = ../CppUTest
endif
CPP_PLATFORM = Gcc

SRC_DIRS = \
    src\
    src/*

# to pick specific files (rather than directories) use this:
SRC_FILES =

TEST_SRC_DIRS = \
    tests \
    tests/*

MOCKS_SRC_DIRS = \
    mocks \

INCLUDE_DIRS =\
  .\
  include \
  include/util \
  $(CPPUTEST_HOME)/include/ \
  $(CPPUTEST_HOME)/include/Platforms/Gcc\
  mocks

CPPUTEST_WARNINGFLAGS = -Wall -Werror -Wswitch-default
CPPUTEST_WARNINGFLAGS += -Wconversion -Wswitch-enum
LD_LIBRARIES = -lCppUTest -lCppUTestExt

include $(CPPUTEST_HOME)/build/MakefileWorker.mk

