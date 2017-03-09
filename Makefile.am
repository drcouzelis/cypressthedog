# Sources
bin_PROGRAMS = cypressthedog
cypressthedog_CPPFLAGS = -Wall -Werror -DPKGDATADIR='"$(pkgdatadir)"'
cypressthedog_SOURCES = \
  src/cc.c \
  src/datas.h \
  src/draw.c \
  src/inits.c \
  src/location.c \
  src/main.c \
  src/oo.c

# Data - Images
imagesdatadir = $(pkgdatadir)/images
dist_imagesdata_DATA = \
  data/images/bg-sunset.bmp \
  data/images/bg-trees.bmp \
  data/images/cedar.bmp \
  data/images/cypress.bmp \
  data/images/tiles.bmp

# Data - Levels
levelsdatadir = $(pkgdatadir)/levels
dist_levelsdata_DATA = \
  data/levels/levels.txt \
  data/levels/tiles.txt \
  data/levels/level-1.bmp
