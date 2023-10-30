all:
	sudo docker build . -t wordpress
	sudo docker run -t -d --name test -p 80:80 wordpress
clean:
	sudo docker stop test
	sudo docker container prune -f
	sudo docker rmi wordpress
re:
	make clean
	make
