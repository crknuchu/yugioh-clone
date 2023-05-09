FROM archlinux
COPY Yugioh/ /azrs

# Update the repositories with Arch's package manager (pacman)
RUN pacman -Sy

# Install some often used developer programs (gcc, make...)
RUN yes | pacman -S base-devel

# Install CMake
RUN yes | pacman -S cmake

# Install Qt5
RUN yes | pacman -S qt5-base
