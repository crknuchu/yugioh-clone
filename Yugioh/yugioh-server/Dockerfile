FROM archlinux:latest

# TODO: git clone?
COPY ./CMakeLists.txt /usr/src/yugioh-server/
COPY ./headers /usr/src/yugioh-server/headers/
COPY ./sources /usr/src/yugioh-server/sources/

WORKDIR /usr/src/yugioh-server


# Update the repositories with Arch's package manager (pacman)
RUN pacman -Sy

# Refresh all package lists / mirrors
RUN yes | pacman -Syyu

RUN yes | pacman -S cmake make gcc

RUN yes | pacman -S qt5-base qt5-multimedia

RUN cmake -G "Unix Makefiles" -S . -B ./build
RUN cmake ./build

WORKDIR /usr/src/yugioh-server/build

RUN make


CMD ["./Yugioh-Server"]
