DOMAIN		= vmalassi.42.fr
DATA_PATH	= /home/vmalassi/data

all: 	up

up:	setup
	docker compose -f ./srcs/docker-compose.yml up -d --build

down:
	docker compose -f ./srcs/docker-compose.yml down

start:
	docker compose -f ./srcs/docker-compose.yml start

stop:
	docker compose -f ./srcs/docker-compose.yml stop

status:
	cd srcs && docker compose ps && cd ..

logs:
	cd srcs && docker compose logs && cd ..

script:
	if ! grep -q "$(DOMAIN)" "/etc/hosts"; then \
		echo "127.0.0.1 $(DOMAIN)" | sudo tee -a /etc/hosts; \
	fi

setup: script
	sudo mkdir -p /home/vmalassi/
	sudo mkdir -p ${DATA_PATH}
	sudo mkdir -p ${DATA_PATH}/mariadb
	sudo mkdir -p ${DATA_PATH}/wordpress

clean: down
	sudo rm -rf ${DATA_PATH}

fclean: clean
	docker system prune -f -a --volumes
	docker volume rm srcs_mariadb srcs_wordpress

.PHONY: all up down start stop status logs prune clean fclean
