FROM ubuntu:latest
WORKDIR /app
RUN apt update
RUN apt install -y build-essential
RUN apt install -y cmake
RUN apt install -y git
RUN apt install -y tmux
RUN apt install -y python3
RUN apt install -y gh
RUN apt install -y fuse libfuse2
RUN apt install -y kmod
RUN apt install -y xz-utils
RUN apt install -y uncrustify
RUN apt install -y curl
RUN apt install -y clangd
RUN apt install -y unzip
RUN apt install -y libboost-all-dev
RUN apt install -y libjsoncpp-dev
RUN apt install -y qt6-base-dev
RUN git clone https://github.com/LazyVim/starter ~/.config/nvim
RUN git clone https://github.com/emscripten-core/emsdk.git
RUN cd emsdk && git pull
RUN cd emsdk && ./emsdk install latest
RUN cd emsdk && ./emsdk activate latest
COPY run_neovim.sh .
COPY conform.lua /root/.config/nvim/lua/plugins/
COPY core.lua /root/.config/nvim/lua/plugins/
COPY mason.lua /root/.config/nvim/lua/plugins/
COPY nvim-lspconfig.lua /root/.config/nvim/lua/plugins/
COPY options.lua /root/.config/nvim/lua/config/
COPY uncrustify.cfg /root/
COPY .tmux.conf /root/
RUN apt install -y ripgrep
RUN apt install -y pkg-config
RUN apt install -y libpq-dev
RUN git clone https://github.com/jtv/libpqxx.git
RUN cd libpqxx && cmake . && cmake --build . && cmake --install .
RUN curl -L -o nvim.appimage https://github.com/neovim/neovim/releases/latest/download/nvim.appimage
RUN chmod u+x nvim.appimage
CMD ["./run_neovim.sh"]
