FROM ubuntu:16.04
MAINTAINER Vishnu Easwaran "easwaranvishnu@gmail.com"

# environment variables to avoid that dpkg-reconfigure 
# tries to ask the user any questions
#
ENV DEBIAN_FRONTEND noninteractive
ENV DEBCONF_NONINTERACTIVE_SEEN true

# Essentials needed for development
RUN apt update && apt -y upgrade && apt -y install \
	build-essential \
	python \
	python3 \
	libncurses5-dev \
	libsigsegv-dev \
	rsync \
	wget \
	cpio \
	unzip \
	bc \
	vim \
	gcc-multilib \
	flex \
	bison \
	tar \
	locales \
	perl \
	sed \
	gcc \
	g++ \
	git

# seeting locales; might need for buildroot
RUN sed -i "s/^# en_US.UTF-8/en_US.UTF-8/" /etc/locale.gen && locale-gen && update-locale LANG=en_US.UTF-8

# Clean up APT when done.
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

#
# prepare startup files in /src/misc
#
RUN mkdir -p      /src/misc
ADD startup.sh    /src/misc/startup.sh
RUN chmod a+x     /src/misc/startup.sh
ENTRYPOINT cd     /src/misc ; ./startup.sh

