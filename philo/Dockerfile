FROM debian:stretch

# Update package manager
RUN apt-get update \
&& apt-get upgrade -y \
&& apt-get install -y build-essential \
&& apt-get install -y valgrind \
&& apt-get install -y clang \
&& apt-get install libpthread-stubs0-dev

WORKDIR /valgrind
