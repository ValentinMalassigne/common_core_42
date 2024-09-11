DOMAIN		= vmalassi.42.fr
DATA_PATH	= /home/vmalassi/data

all: up

up:	setup
	docker compose -f ./srcs/docker-compose.yml up -d --build

down:
	docker compose -f ./srcs/docker-compose.yml down

start:
	docker compose -f ./srcs/docker-compose.yml start

stop:
	docker compose -f ./srcs/docker-compose.yml stop

setup: 
	sudo mkdir -p /home/vmalassi/
	sudo mkdir -p ${DATA_PATH}
	sudo mkdir -p ${DATA_PATH}/mariadb
	sudo mkdir -p ${DATA_PATH}/wordpress

clean: down
	sudo rm -rf ${DATA_PATH}

fclean: clean
	docker system prune -f -a --volumes
	docker volume rm srcs_mariadb srcs_wordpress

.PHONY: all up down start stop setup clean fclean
