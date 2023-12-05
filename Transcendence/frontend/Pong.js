export class Pong
{
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
        ctx.canvas.width  = this.main.game_info.data.width;
        ctx.canvas.height = this.main.game_info.data.height;
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
        dom_start = document.getElementById("start");
        dom_start.addEventListener("click", () => {
            $.ajax({
                url: '/start_game/',
                method: 'POST',
                data: {
                    "user": this.main.user,
                    "game_id": this.main.game_info.id
                },
                success: (response) => {
                    if (response != "started")
                        this.main.dom_status.textContent = response;
                },
                error: function(error) {
                    console.error('Error: start POST fail', error.message);
                }
            });
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
                if (response != "wait")
                {
                    this.data = response;
                    this.draw();
                    this.to_do = "";
                }
                setTimeout(() => {this.loop();}, this.update_time_interval);
            },
            error: function(error) {
                console.error('Error: pong state POST fail', error.message);
            }
        });
    }

	draw() {
		// Clear the canvas
		this.ctx.clearRect(0, 0, this.main.game_info.data.width, this.main.game_info.data.height);

		// Draw paddles
		this.ctx.fillStyle = '#8b3a62';
        this.data.position.forEach((y, i) => {
		    this.ctx.fillRect(
                this.main.game_info.data.x[i],
                y,
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
