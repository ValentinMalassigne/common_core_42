VOLUME_PATH = /home/vmalassi/data

all: init
	sudo docker compose -f srcs/docker-compose.yml up --build

stop:
	docker compose -f srcs/docker-compose.yml stop

stop:
	docker compose -f srcs/docker-compose.yml start

down:
	docker compose -f srcs/docker-compose.yml down -v

init:
	sudo mkdir -p /home/vmalassi
	sudo mkdir -p ${VOLUME_PATH}
	sudo mkdir -p ${VOLUME_PATH}/mariadb
	sudo mkdir -p ${VOLUME_PATH}/wordpress

clean: down
	sudo rm -rf ${DATA_PATH}

fclean: clean
	docker system prune -f -a --volumes
	docker volume rm srcs_mariadb-data srcs_wordpress-data