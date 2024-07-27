#!/bin/bash
source ~/source_build/emsdk/emsdk_env.sh;
cd cmake;
emcmake cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .;
cmake --build .;
# cp bin/* ../docker;
# cd ../docker;
# sudo docker build . -t jod_client_web