run:
	docker build -t apache2-test .
	docker run --name apache2-test --rm -dit -p 8080:80 apache2-test

run-privileged:
	docker build -t apache2-test .
	docker run --privileged --name apache2-test --rm -dit -p 8080:80 apache2-test

stop:
	docker stop apache2-test
