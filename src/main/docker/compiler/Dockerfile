# @see https://hub.docker.com/_/ubuntu
FROM ubuntu:26.04 AS runner

# Installs dependencies.
RUN apt update --yes \
	&& apt install --no-install-recommends --yes \
		bison \
		build-essential \
		cmake \
		flex \
		gcc \
		gdb \
		gdbserver \
		make \
	&& rm --force --recursive /var/lib/apt/lists/*
