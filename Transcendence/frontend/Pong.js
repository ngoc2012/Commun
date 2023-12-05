export class Pong
{
	height = 400;
	width = 800;
	paddleWidth = 10;
	paddleHeight = 60;
    to_do = "";
    data;

	constructor(m) {
        this.main = m;
    }

	init() {
		this.canvas = document.getElementById('pongCanvas');
		this.ctx = this.canvas.getContext('2d');
        // Handle keyboard input
        document.addEventListener('keydown', function (event) {
            switch (event.key) {
                case 'ArrowUp':
                    to_do = "up";
                    break;
                case 'ArrowDown':
                    to_do = "down";
                    break;
            }
        });

        /*
        document.addEventListener('keyup', function (event) {
            switch (event.key) {
                case 'ArrowUp':
                case 'ArrowDown':
                    rightPaddle.dy = 0;
                    break;
            }
        });
        */

	}

	loop() {
        $.ajax({
            url: '/pong_state/',
            method: 'POST',
            data: {
                "user": this.main.user,
                "to_do": this.to_do
            },
            success: (response) => {
                if (response == "wait")
                this.data = 
                this.main.name = "pong";
                this.main.id = response.game_id;
                this.main.status = "waiting";
                this.main.dom_status.textContent = "New game " + this.main.name + " " + this.main.id + " created. Wait for players...";
                to_do = "";
            },
            error: function(error) {
                console.error('Error: invite POST fail', error.message);
            }
        });
    }

	draw() {
		// Clear the canvas
		this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);

		// Draw paddles
		this.ctx.fillStyle = '#8b3a62';
		this.ctx.fillRect(this.leftPaddle.x, this.leftPaddle.y, this.leftPaddle.width, this.leftPaddle.height);
		this.ctx.fillRect(this.rightPaddle.x, this.rightPaddle.y, this.rightPaddle.width, this.rightPaddle.height);

		// Draw this.ball
		this.ctx.beginPath();
		this.ctx.arc(this.ball.x, this.ball.y, this.ball.radius, 0, Math.PI * 2);
		this.ctx.fillStyle = '#00ffcc';
		this.ctx.fill();
		this.ctx.closePath();
	}
}
