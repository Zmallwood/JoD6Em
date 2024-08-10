#!/bin/sh

cd cmake
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -G "Unix Makefiles" .;
make;
