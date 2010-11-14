## Makefile.am -- Process this file with automake to produce Makefile.in

noinst_PROGRAMS = get_distance get_distance_intensity get_multiecho get_multiecho_intensity sensor_parameter sync_time_stamp

get_distance_SOURCES = get_distance.cpp Connection_information.cpp Connection_information.h
get_distance_intensity_SOURCES = get_distance_intensity.cpp Connection_information.cpp Connection_information.h
get_multiecho_SOURCES = get_multiecho.cpp Connection_information.cpp Connection_information.h
get_multiecho_intensity_SOURCES = get_multiecho_intensity.cpp Connection_information.cpp Connection_information.h
sensor_parameter_SOURCES = sensor_parameter.cpp Connection_information.cpp Connection_information.h
sync_time_stamp_SOURCES = sync_time_stamp.cpp Connection_information.cpp Connection_information.h

INCLUDES = -I$(top_srcdir)/src
LDADD = -L$(top_srcdir)/src
