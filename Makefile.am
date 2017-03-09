# Sources
bin_PROGRAMS = cypressthedog
cypressthedog_CPPFLAGS = -Wall -Werror -DPKGDATADIR='"$(pkgdatadir)"'
cypressthedog_SOURCES = \
  src/cc.c \
  src/cnt_main.c \
  src/datas.h \
  src/draw.c \
  src/inits.c \
  src/location.c \
  src/oo.c

# Data - Images
imagesdatadir = $(pkgdatadir)/images
dist_imagesdata_DATA = \
  data/images/cypress.bmp \
  data/images/far_trees.bmp \
  data/images/oo_cedar.bmp \
  data/images/sunset.bmp \
  data/images/tile1.bmp

# Data - Levels
levelsdatadir = $(pkgdatadir)/levels
dist_levelsdata_DATA = \
  data/levels/cnt_levl.txt \
  data/levels/cnt_tile.txt \
  data/levels/level1.bmp
