# Author:  Menglong TAN <tanmenglong@gmail.com>
# Date:    Sun Aug 21 14:08:41 2016
#
# Make Target:
# ------------
# The Makefile provides the following targets to make:
#   $ make           compile and link
#   $ make clean     clean objects and the executable file
#
#===========================================================================

include ../Makefile.env

BUILD_TARGETS = libgoeasemob.a

INC = -I../include -I./ -I$(EM_DEPS)/include
LIB = -leasemob -L$(EM_DEPS)

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

.PHONY : all clean

all : $(BUILD_TARGETS)

$(BUILD_TARGETS) : $(OBJ)
	ar -cr -o $@ $^

clean:
	rm -rf $(OBJ) $(BUILD_TARGETS)
