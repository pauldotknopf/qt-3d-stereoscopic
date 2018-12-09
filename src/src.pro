TEMPLATE = subdirs

SUBDIRS += stereo3d
sensors.subdir = stereo3d

SUBDIRS += imports
imports.subdir = imports
imports.depends = stereo3d
