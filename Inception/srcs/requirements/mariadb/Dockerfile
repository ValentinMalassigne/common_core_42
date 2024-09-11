FROM	alpine:3.19

RUN	apk update && apk upgrade &&\
	apk add mariadb mariadb-client
	
COPY	./tools/setup_mariadb.sh /tmp/setup_mariadb.sh
RUN	chmod +x /tmp/setup_mariadb.sh

COPY ./conf/mariadb-server.cnf /etc/my.cnf.d/mariadb-server.cnf

EXPOSE 3306

ENTRYPOINT	[ "sh", "/tmp/setup_mariadb.sh" ]
