all:
	sudo docker build . -t wordpress
	sudo docker run -t -d --name test -p 80:80 wordpress
clean:
	sudo docker stop test
