#--------------------------------------------------------
# system
#--------------------------------------------------------
UNAME = $(shell uname)

#--------------------------------------------------------
# target
#--------------------------------------------------------
TARGET = pong

#--------------------------------------------------------
# directories
#--------------------------------------------------------
GIT_DIR = ./
SRC_DIR = $(GIT_DIR)src/
INC_DIR = $(GIT_DIR)include/
INT_DIR = $(GIT_DIR)

BIN_DIR = ./bin/

OBJ_DIR = ./obj/$(UNAME)/

ifeq ($(OS), Linux)
	include Makefile.linux.mk
else
	include Makefile.windows.mk
endif
