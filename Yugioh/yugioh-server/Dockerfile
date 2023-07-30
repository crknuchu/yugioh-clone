FROM archlinux:latest

# Update the repositories with Arch's package manager (pacman)
RUN pacman -Sy

# Refresh all package lists / mirrors
# TODO: --confirm instead of yes
RUN yes | pacman -Syyu

RUN yes | pacman -S cmake make gcc

RUN yes | pacman -S qt5-base qt5-multimedia

WORKDIR /usr/src/yugioh-server

# TODO: Dockerignore, COPY . /usr/src/yugioh-server
COPY ./CMakeLists.txt .
COPY ./headers ./headers/
COPY ./sources ./sources/

RUN cmake -G "Unix Makefiles" -S . -B ./build
RUN cmake ./build

WORKDIR /usr/src/yugioh-server/build

RUN make

CMD ["./Yugioh-Server"]
