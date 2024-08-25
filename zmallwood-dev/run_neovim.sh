#!/bin/bash

modprobe fuse
. /app/emsdk/emsdk_env.sh
git config --global --add safe.directory '*'
cd /app/code/hobby_cpp/JoD6Em/Repository/WorkingDirectory/
tmux -u new-session \; split-window -v -l 20% \; selectp -t 0 \; send-keys -t "$pane" C-z "/app/nvim.appimage ." Enter \; selectp -t 1 \; send-keys -t "$pane" C-z "cd ../Client" Enter \; split-window -h -l 66% \; send-keys -t "$pane" C-z "cd ../Server" Enter \; split-window -h   \; send-keys -t "$pane" C-z "cd ../WorldEditor" Enter
