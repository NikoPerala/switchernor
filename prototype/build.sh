#!/usr/bin/sh

set -xe

gcc src/main.c src/gui_utils.c -lraylib -o prototype
