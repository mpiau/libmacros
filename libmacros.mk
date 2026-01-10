# Simply include this .mk file in your Makefile to use that library.

LIBMACROS_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
CFLAGS += -I$(LIBMACROS_DIR)include
