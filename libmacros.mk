# Simply include this .mk file in your Makefile to use that library.

# Avoid being included multiple times if used multiple times as a dependency. 
ifndef LIBMACROS_INCLUDE
LIBMACROS_INCLUDE := 1

LIBMACROS_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
CFLAGS += -I$(LIBMACROS_DIR)include

endif 