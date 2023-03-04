OS_HOME=$(realpath ../../)
OS_IMAGE="os-runner-image"
OS_CONTAINER="os-runner"
HOSTNAME="os"

.PHONY: docker-image start attach clean

docker-image:
	docker build -t $(OS_IMAGE) .

start: docker-image
	docker run	\
		--detach	\
		--name $(OS_CONTAINER)	\
		--hostname=$(HOSTNAME)	\
		--mount type=bind,source="$(OS_HOME)",target=/home/student/operating-systems	\
		--cap-add SYS_ADMIN	\
		--env "TERM=xterm-256color"	\
		-it $(OS_IMAGE)

attach: docker-image
	docker exec -it $(OS_CONTAINER) bash

clean:
	docker container stop $(OS_CONTAINER)
	docker container rm $(OS_CONTAINER)
