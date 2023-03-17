OS_HOME=$(realpath ../../)
OS_LOCAL_IMAGE="os-runner:$(shell git hash-object Dockerfile)"
OS_IMAGE="ghcr.io/open-education-hub/os-runner:latest"
OS_CONTAINER="os-runner"
HOSTNAME="os"

.PHONY: docker-image start attach pull clean

pull:
	docker pull $(OS_IMAGE)

docker-image:
ifeq ("$(shell docker images -q $(OS_LOCAL_IMAGE))", "")
	docker buildx build --platform linux/amd64 -t $(OS_LOCAL_IMAGE) .
endif


start: pull
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
