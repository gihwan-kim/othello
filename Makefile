# googletest	: make my_google_test
# main.cpp		: make or make main => othello


# you should change dir to your googletest dir
GTEST_DIR= ./googletest/googletest

CPPFLAGS += -isystem $(GTEST_DIR)/include $(INC)

CXXFLAGS += -pthread $(INC)
# CXXFLAGS += $(INC)

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# gdb 디버그 할떄 사용
# DEBUGG = -g

TERM_HEADER = \
				Context.h \
				StoneFactory.h \
				Stone.h \
				State.h \
				CoordCheckState.h \
				UserInputState.h \
				UpdateBoardState.h\
				WinnerCheckState.h \
				FinalState.h \
				GameEndState.h \
				Utils.h \
				Viewr.h

TERM_HEADER_DIR = ./include
TERM_HEADER_LIST = $(addprefix $(TERM_HEADER_DIR)/, $(TERM_HEADER))

INC = -I./include

CONTROLLER_SRCS = 	\
					Context.cc
CONTROLLER_SRCS_DIR = ./src/controller


STATE_SRCS = \
				State.cc \
				CoordCheckState.cc \
				UserInputState.cc \
				UpdateBoardState.cc \
				WinnerCheckState.cc \
				FinalState.cc \
				GameEndState.cc
STATE_SRCS_DIR = ./src/state

STONE_SRCS =	\
				Stone.cc \
				StoneFactory.cc
STONE_SRCS_DIR = ./src/stone

VIEWR_SRCS = Viewer.cc
VIEWR_SRCS_DIR = ./src/viewer


SRCS_LIST =  \
		$(addprefix $(CONTROLLER_SRCS_DIR)/, $(CONTROLLER_SRCS)) \
		$(addprefix $(STONE_SRCS_DIR)/, $(STONE_SRCS)) \
		$(addprefix $(VIEWR_SRCS_DIR)/, $(VIEWR_SRCS)) \
		$(addprefix $(STATE_SRCS_DIR)/, $(STATE_SRCS)) \
		./src/Utils.cc
OBJS = $(SRCS_LIST:%.cc=%.o)

EXE_NAME = othello

all : main

clean :
	rm -f gtest.a gtest_main.a *.o $(EXE_NAME) my_google_test $(OBJS)

gtest-all.o : $(GTEST_SRCS_)
	g++ $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	g++ $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# # main : $(GTEST_HEADERS) $(TERM_HEADER_LIST)
main : ./src/main.cc $(OBJS) ./include $(SRCS_LIST)
	g++ --std=c++17 $(INC) $(DEBUGG) ./src/main.cc $(OBJS) -o $(EXE_NAME)

main_test.o : ./src/game_test.cc $(GTEST_HEADERS)
	g++ $(CPPFLAGS) $(CXXFLAGS) --std=c++17 -c ./src/game_test.cc -o $@

my_google_test : gtest_main.a $(OBJS) main_test.o
	g++ $(CPPFLAGS) $(CXXFLAGS) --std=c++17 $^ -o $@

.PHONY: all clean main
