FROM	alpine:3.19

RUN		apk update && apk upgrade &&\
		apk add nginx

COPY	./conf/nginx.conf /etc/nginx/http.d/default.conf

RUN		apk add openssl

COPY	./tools/generate_certificate.sh /tmp/generate_certificate.sh
RUN		chmod +x /tmp/generate_certificate.sh
RUN		/tmp/generate_certificate.sh

EXPOSE	443

ENTRYPOINT	["nginx", "-g", "daemon off;"]
