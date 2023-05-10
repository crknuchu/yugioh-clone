FROM archlinux
# Update the repositories with Arch's package manager (pacman)
RUN pacman -Sy

# Refresh all package lists / mirrors
RUN yes | pacman -Syyu

# Install some often used developer programs (gcc, make...)
RUN yes | pacman -S base-devel

# Install CMake
RUN yes | pacman -S cmake

# Install Qt5
RUN yes | pacman -S qt5-base qt5-multimedia

# Install git
RUN yes | pacman -S git

# Clone the project repo (specifically the azrs/kubni branch)
RUN git clone -b azrs/kubni https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2022-2023/09-yugioh.git

# Run cmake
RUN cmake -DCMAKE_BUILD_TYPE=Release -S 09-yugioh/Yugioh -B 09-yugioh/build
RUN cmake --build 09-yugioh/build
