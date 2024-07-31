#!/bin/sh

find client/src/ -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i
find server/src/ -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i
