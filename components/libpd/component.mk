CFLAGS += -DBYTE_ORDER=LE
CFLAGS += -DLITTLE_ENDIAN=LE
CFLAGS += -D_POSIX_THREADS
CFLAGS += -D__GNU__
CFLAGS += -DPD
CFLAGS += -UHAVE_LIBDL
CFLAGS += -DHAVE_UNISTD_H
CFLAGS += -Wno-int-to-pointer-cast
CFLAGS += -Wno-pointer-to-int-cast
CFLAGS += -fPIC
CFLAGS += -Wno-error=char-subscripts
CFLAGS += -Wno-unused
CFLAGS += -Wno-error=unused-label
CFLAGS += -DUSEAPI_DUMMY

#	libpd/pure-data/src/d_soundfile.o \
#

COMPONENT_OBJS = \
	libpd/pure-data/src/d_arithmetic.o \
	libpd/pure-data/src/d_array.o \
	libpd/pure-data/src/d_ctl.o \
	libpd/pure-data/src/d_dac.o \
	libpd/pure-data/src/d_delay.o \
	libpd/pure-data/src/d_fft_fftsg.o \
	libpd/pure-data/src/d_fft.o \
	libpd/pure-data/src/d_filter.o \
	libpd/pure-data/src/d_global.o \
	libpd/pure-data/src/d_math.o \
	libpd/pure-data/src/d_misc.o \
	libpd/pure-data/src/d_osc.o \
	libpd/pure-data/src/d_resample.o \
	libpd/pure-data/src/d_ugen.o \
	libpd/pure-data/src/g_all_guis.o \
	libpd/pure-data/src/g_array.o \
	libpd/pure-data/src/g_bang.o \
	libpd/pure-data/src/g_canvas.o \
	libpd/pure-data/src/g_clone.o \
	libpd/pure-data/src/g_editor.o \
	libpd/pure-data/src/g_graph.o \
	libpd/pure-data/src/g_guiconnect.o \
	libpd/pure-data/src/g_hdial.o \
	libpd/pure-data/src/g_hslider.o \
	libpd/pure-data/src/g_io.o \
	libpd/pure-data/src/g_mycanvas.o \
	libpd/pure-data/src/g_numbox.o \
	libpd/pure-data/src/g_readwrite.o \
	libpd/pure-data/src/g_rtext.o \
	libpd/pure-data/src/g_scalar.o \
	libpd/pure-data/src/g_template.o \
	libpd/pure-data/src/g_text.o \
	libpd/pure-data/src/g_toggle.o \
	libpd/pure-data/src/g_traversal.o \
	libpd/pure-data/src/g_vdial.o \
	libpd/pure-data/src/g_vslider.o \
	libpd/pure-data/src/g_vumeter.o \
	libpd/pure-data/src/m_atom.o \
	libpd/pure-data/src/m_binbuf.o \
	libpd/pure-data/src/m_class.o \
	libpd/pure-data/src/m_conf.o \
	libpd/pure-data/src/m_glob.o \
	libpd/pure-data/src/m_memory.o \
	libpd/pure-data/src/m_obj.o \
	libpd/pure-data/src/m_pd.o \
	libpd/pure-data/src/m_sched.o \
	libpd/pure-data/src/s_audio_dummy.o \
	libpd/pure-data/src/s_audio.o \
	libpd/pure-data/src/s_file.o \
	libpd/pure-data/src/s_inter.o \
	libpd/pure-data/src/s_loader.o \
	libpd/pure-data/src/s_main.o \
	libpd/pure-data/src/s_path.o \
	libpd/pure-data/src/s_print.o \
	libpd/pure-data/src/s_utf8.o \
	libpd/pure-data/src/x_acoustics.o \
	libpd/pure-data/src/x_arithmetic.o \
	libpd/pure-data/src/x_array.o \
	libpd/pure-data/src/x_connective.o \
	libpd/pure-data/src/x_gui.o \
	libpd/pure-data/src/x_interface.o \
	libpd/pure-data/src/x_list.o \
	libpd/pure-data/src/x_midi.o \
	libpd/pure-data/src/x_misc.o \
	libpd/pure-data/src/x_net.o \
	libpd/pure-data/src/x_scalar.o \
	libpd/pure-data/src/x_text.o \
	libpd/pure-data/src/x_time.o \
	libpd/pure-data/src/x_vexp_fun.o \
	libpd/pure-data/src/x_vexp_if.o \
	libpd/pure-data/src/x_vexp.o \
	libpd/libpd_wrapper/s_libpdmidi.o \
	libpd/libpd_wrapper/x_libpdreceive.o \
	libpd/libpd_wrapper/z_hooks.o \
	libpd/libpd_wrapper/z_libpd.o

libpd/pure-data/s_inter.c: CFLAGS += -D__rtems__

# libpd/libpd_wrapper/util/z_print_util.o \
# libpd/libpd_wrapper/util/z_queued.o \
# libpd/libpd_wrapper/util/ringbuffer.o \
# libpd/pure-data/extra/bob~/bob~.o \
# libpd/pure-data/extra/bonk~/bonk~.o \
# libpd/pure-data/extra/choice/choice.o \
# libpd/pure-data/extra/fiddle~/fiddle~.o \
# libpd/pure-data/extra/loop~/loop~.o \
# libpd/pure-data/extra/lrshift~/lrshift~.o \
# libpd/pure-data/extra/pique/pique.o \
# libpd/pure-data/extra/sigmund~/sigmund~.o \
# libpd/pure-data/extra/stdout/stdout.o


COMPONENT_SRCDIRS := libpd/libpd_wrapper libpd/pure-data/src

COMPONENT_ADD_INCLUDEDIRS += libpd/libpd_wrapper libpd/pure-data/src

include $(IDF_PATH)/make/component_common.mk
