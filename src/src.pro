TEMPLATE = subdirs

SUBDIRS += stereo3d
sensors.subdir = stereo3d
sensors.target = sub-stereo3d

SUBDIRS += imports
imports.subdir = imports
imports.target = sub-imports
imports.depends = stereo3d
