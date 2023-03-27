OS_HOME=$(realpath ../../)
OS_LOCAL_IMAGE="os-runner:$(shell git hash-object Dockerfile)"
OS_IMAGE="ghcr.io/open-education-hub/os-runner:latest"
OS_CONTAINER="os-runner"
HOSTNAME="os"

.PHONY: docker-image start attach pull clean

pull:
	docker pull $(OS_IMAGE)

docker-image: ## Build the docker image.
ifeq ("$(shell docker images -q $(OS_LOCAL_IMAGE))", "")
	docker buildx build --platform linux/amd64 -t $(OS_LOCAL_IMAGE) .
endif


start: pull ## Start the container in the background if it is not already running.
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


attach: start ## Attach to the container.
	docker exec -it $(OS_CONTAINER) bash

clean: ## Stop and remove the container.
	docker container stop $(OS_CONTAINER)
	docker container rm $(OS_CONTAINER)

help: ## Show this help menu and exit.
	@awk 'BEGIN {	\
		FS = ":.*##";	\
		printf "OS class container environment.\n\n";	\
		printf "\033[1mUSAGE\033[0m\n";	\
		printf "  make [VAR=... [VAR=...]] \033[36mTARGET\033[0m\n\n";	\
		printf "\033[1mTARGETS\033[0m\n";	\
	}	\
	/^[a-zA-Z_-]+:.*?##/ {	\
		printf "  \033[36m%-23s\033[0m %s\n", $$1, $$2	\
	}	\
	/^##@/ {	\
		printf "\n\033[1m%s\033[0m\n", substr($$0, 5)	\
	} ' $(MAKEFILE_LIST)
