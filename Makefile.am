AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
bin_PROGRAMS = googet shuffler
noinst_LIBRARIES =
googet_SOURCES = src/googet.cpp src/frontend.cpp
googet_LDADD = -lstdc++ -lcurl -L.
googet_CPPFLAGS = -O3 -std=c++11
googet_LDFLAGS =
shuffler_SOURCES = src/googet.cpp src/shuffler.cpp
shuffler_LDADD = -lstdc++ -lcurl -L.
shuffler_CPPFLAGS = -O3 -std=c++11
shufflerdir = bin
AM_CXXFLAGS = -Wall
