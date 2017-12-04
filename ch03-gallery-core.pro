TEMPLATE = subdirs

SUBDIRS += \
    gallery-core \
    gallery-desktop \
    gallery-mobile
# depends attribute helps qmake process project in parallet when possible
gallery-desktop.depends = gallery-core
#gallery-mobile.depends = gallery-core

