FROM ubuntu:18.04

ARG INSTALLER_NAME
COPY files/accept-eula.sh files/${INSTALLER_NAME} /

# install dependences:
RUN dpkg --add-architecture i386 && \
	apt-get update && \
	DEBIAN_FRONTEND=noninteractive apt-get install -y -q \
		build-essential \
		neovim \
		sudo \
		tofrodos \
		iproute2 \
		gawk \
		net-tools \
		expect \
		libncurses5-dev \
		tftpd \
		update-inetd \
		libssl-dev \
		flex \
		bison \
		libselinux1 \
		gnupg \
		wget \
		socat \
		gcc-multilib \
		libidn11 \
		libsdl1.2-dev \
		libglib2.0-dev \
		lib32z1-dev \
		libgtk2.0-0 \
		libtinfo5 \
		xxd \
		screen \
		pax \
		diffstat \
		xvfb \
		xterm \
		texinfo \
		gzip \
		unzip \
		cpio \
		chrpath \
		autoconf \
		lsb-release \
		libtool \
		libtool-bin \
		locales \
		kmod \
		git \
		rsync \
		bc \
		u-boot-tools \
		python \
		zlib1g:i386 && \
	apt-get clean && \
	rm -rf /var/lib/apt/lists/* && \
	locale-gen en_US.UTF-8 && \
	update-locale
ENV LANG en_US.UTF-8

# make a petalinux user
RUN adduser --disabled-password --gecos '' petalinux && \
	usermod -aG sudo petalinux && \
	echo 'petalinux ALL=(ALL) NOPASSWD: ALL' >> /etc/sudoers

# run the install
RUN chmod a+rx /${INSTALLER_NAME} /accept-eula.sh && \
	mkdir -p /opt/Xilinx && \
	chmod 777 /opt/Xilinx && \
	cd /tmp && \
	sudo -u petalinux -i /accept-eula.sh /${INSTALLER_NAME} --dir='/opt/Xilinx/petalinux' && \
	rm -f /${INSTALLER_NAME} /accept-eula.sh

# make /bin/sh symlink to bash instead of dash:
RUN echo 'dash dash/sh boolean false' | debconf-set-selections
RUN DEBIAN_FRONTEND=noninteractive dpkg-reconfigure dash

# change default user
USER petalinux
RUN mkdir /home/petalinux/workspace
WORKDIR /home/petalinux/workspace

# create bin folder
ENV BIN_FOLDER /home/petalinux/bin
RUN mkdir "${BIN_FOLDER}"
RUN echo 'echo "$PATH" | grep -qF "${BIN_FOLDER}" || \
export PATH="$(find "${BIN_FOLDER}" -type d -printf '%p:')$PATH"' >> /home/petalinux/.bashrc

# add petalinux tools to path
RUN echo 'source /opt/Xilinx/petalinux/settings.sh' >> /home/petalinux/.bashrc
