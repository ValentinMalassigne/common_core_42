FROM debian:buster

RUN apt update -y
RUN apt upgrade -y

RUN apt-get install mariadb-client -y

COPY	./conf/configure-mariadb.sh /tmp/configure-mariadb.sh
RUN	chmod +x /tmp/configure-mariadb.sh

ENTRYPOINT	[ "bash", "/tmp/configure-mariadb.sh" ]