OS_HOME=$(realpath ../../)
OS_IMAGE="os-runner-image:$(shell git hash-object Dockerfile)"
OS_CONTAINER="os-runner"
HOSTNAME="os"

.PHONY: docker-image start attach clean

docker-image:
ifeq ("$(shell docker images -q $(OS_IMAGE))", "")
	docker buildx build --platform linux/amd64 -t $(OS_IMAGE) .
endif

start: docker-image
ifneq ("$(shell docker container inspect -f '{{.State.Running}}' os-runner)", "true")
	docker run	\
		--detach	\
		--name $(OS_CONTAINER)	\
		--hostname=$(HOSTNAME)	\
		--mount type=bind,source="$(OS_HOME)",target=/home/student/operating-systems	\
		--cap-add SYS_ADMIN	\
		--env "TERM=xterm-256color"	\
		-it $(OS_IMAGE)
endif

attach: start
	docker exec -it $(OS_CONTAINER) bash

clean:
	docker container stop $(OS_CONTAINER)
	docker container rm $(OS_CONTAINER)
