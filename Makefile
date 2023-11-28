REPO_NAME = operating-systems
IMAGE_NAME = $(REPO_NAME)/docusaurus:latest
CONTAINER_NAME = open-edu-hub-$(REPO_NAME)-bash
OUTPUT_DIR = $$PWD/.output/$(REPO_NAME)

.PHONY: all buildimg build serve run_bash enter_bash stop_bash clean cleanall

all: build

buildimg:
	docker build -f ./Dockerfile --tag $(IMAGE_NAME) .

build: buildimg
	@echo "Building content. This will take a while (several minutes) ..."
	@echo "After the build, run"
	@echo ""
	@echo "       make serve"
	@echo ""
	@mkdir -p $(OUTPUT_DIR)
	docker run --rm -v $$PWD/:/content -v $(OUTPUT_DIR):/output $(IMAGE_NAME)

serve:
	@echo "Point your browser to http://localhost:8080/$(REPO_NAME)"
	@cd $(OUTPUT_DIR)/.. && python3 -m http.server 8080

run_bash: buildimg
	@mkdir -p $(OUTPUT_DIR)
	docker run -d -it --entrypoint /bin/bash --name $(CONTAINER_NAME) -v $$PWD/:/content -v $(OUTPUT_DIR):/output $(IMAGE_NAME)

enter_bash:
	docker exec -it $(CONTAINER_NAME) /bin/bash

stop_bash:
	-test "$(shell docker container inspect -f '{{.State.Running}}' $(CONTAINER_NAME) 2> /dev/null)" = "true" && docker stop $(CONTAINER_NAME)

clean: stop_bash
	-docker container inspect $(CONTAINER_NAME) > /dev/null 2>&1 && docker rm $(CONTAINER_NAME)
	-sudo rm -fr $(OUTPUT_DIR)

cleanall: clean
	-docker inspect --type=image $(IMAGE_NAME) > /dev/null 2>&1 && docker image rm $(IMAGE_NAME)
