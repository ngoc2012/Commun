export class Pong
{
	height = 400;
	width = 800;
	paddleWidth = 10;
	paddleHeight = 60;
    to_do = "";
    update_time_interval = 2;
    data;
    canvas;
    ctx;

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
                    this.to_do = "up";
                    break;
                case 'ArrowDown':
                    this.to_do = "down";
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
        this.loop();
	}

	loop() {
        $.ajax({
            url: '/pong_state/',
            method: 'POST',
            data: {
                "user": this.main.user,
                "game_id": this.main.game_info.id,
                "to_do": this.to_do
            },
            success: (response) => {
                if (response == "wait")
                    setTimeout(() => {this.loop();}, this.update_time_interval);
                else
                {
                    this.data = response;
                    this.draw();
                    this.to_do = "";
                }
            },
            error: function(error) {
                console.error('Error: pong state POST fail', error.message);
            }
        });
    }

	draw() {
		// Clear the canvas
		this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);

		// Draw paddles
		this.ctx.fillStyle = '#8b3a62';
        this.data.forEach((y, i) => {
		    this.ctx.fillRect(
                this.main.game_info.data.x[i],
                this.data.position[i],
                this.main.game_info.data.paddle_width,
                this.main.game_info.data.paddle_height);
        });

		// Draw this.ball
		this.ctx.beginPath();
		this.ctx.arc(this.ball.x, this.ball.y, this.ball.radius, 0, Math.PI * 2);
		this.ctx.fillStyle = '#00ffcc';
		this.ctx.fill();
		this.ctx.closePath();
	}
}
