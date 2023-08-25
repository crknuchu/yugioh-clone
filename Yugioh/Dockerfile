FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y
RUN apt-get install qtcreator -y
RUN apt-get install build-essential -y
RUN apt install qtbase5-dev qt5-qmake -y
RUN apt-get install qtmultimedia5-dev -y
RUN apt-get install xcb -y

COPY . /usr/src/Yugioh
WORKDIR /usr/src/Yugioh

RUN qmake
RUN make

CMD ["./Yugioh"]