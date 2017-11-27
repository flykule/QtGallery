TEMPLATE = subdirs

SUBDIRS += \
    gallery-core \
    gallery-desktop
# depends attribute helps qmake process project in parallet when possible
gallery-desktop.depends = gallery-core

