
# COMPONENT_ADD_LDFLAGS := -L /esp/project/lib/libpd/libs -l :libpd.so

# COMPONENT_ADD_INCLUDEDIRS += \
# 	../lib/libpd/libpd_wrapper/ \
# 	../lib/libpd/pure-data/src/


COMPONENT_SRCDIRS := . pthread sys freertos
COMPONENT_ADD_INCLUDEDIRS += .
