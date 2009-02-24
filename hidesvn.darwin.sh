#!/bin/sh

DYLD_INSERT_LIBRARIES=/usr/local/lib/libhidesvn.dylib DYLD_FORCE_FLAT_NAMESPACE=yes exec "$@"
