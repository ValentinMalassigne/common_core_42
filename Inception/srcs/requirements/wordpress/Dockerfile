FROM	alpine:3.19

RUN		apk update && apk upgrade &&\
		apk add php81 php81-fpm php81-mysqli \
			php81-mbstring php81-phar &&\
		apk add mariadb-client
	
RUN	ln -s /usr/bin/php81 /usr/bin/php

# RUN		sed -i 's/listen = 127.0.0.1:9000/listen = 9000/g' /etc/php81/php-fpm.d/www.conf
COPY	./conf/www.conf /etc/php81/php-fpm.d/www.conf

RUN	apk add curl &&\
	curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar &&\
	chmod +x wp-cli.phar &&\
	mv wp-cli.phar /usr/bin/wp

COPY	./tools/setup-wordpress.sh /tmp/setup-wordpress.sh
RUN		chmod +x /tmp/setup-wordpress.sh

WORKDIR /var/www/html/wordpress

ENTRYPOINT	[ "sh", "/tmp/setup-wordpress.sh" ]
