all:
	docker build . -t wordpress
	docker run -t -d --name test -p 443:443 -p 80:80 wordpress
clean:
	docker stop test
	docker container prune -f
	docker rmi wordpress
re:
	make clean
	make
