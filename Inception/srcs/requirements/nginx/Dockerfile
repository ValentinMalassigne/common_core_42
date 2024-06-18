FROM debian:buster

RUN apt update -y
RUN apt upgrade -y
RUN apt install nginx -y

RUN apt install vim -y
RUN apt install curl -y

RUN mkdir -p /etc/nginx/ssl
RUN apt install openssl -y
RUN openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt -keyout /etc/nginx/ssl/inception.key -subj "/C=FR/ST=Normandie/L=LeHavre/O=42/OU=Inception/CN=vmalassi.42.fr/UID=vmalassi"

RUN mkdir -p /var/run/nginx
COPY conf/nginx.conf /etc/nginx/nginx.conf

RUN chmod 755 /var/www/html
RUN chown -R www-data:www-data /var/www/html

CMD [ "nginx", "-g", "daemon off;" ]