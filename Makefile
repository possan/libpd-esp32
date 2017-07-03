#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

VERBOSE = 1
PROJECT_NAME := libpdtest

# COMPONENTS := libpdtest
# COMPONENT_ADD_INCLUDEDIRS := components/include

SRCDIRS = main components/libpd/pure-data/src components/libpd/libpd_wrapper

# main/simple.inc: main/simple.pd
# 	xxd -i main/simple.pd main/simple.inc

# main/main.o: main/main.c main/simple.inc

include $(IDF_PATH)/make/project.mk
