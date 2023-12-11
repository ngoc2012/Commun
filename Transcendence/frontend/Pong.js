export class Pong
{
    update_time_interval = 50;
    data;
    canvas;
    ctx;
    info;

	constructor(m, i) {
        this.main = m;
        this.info = i;
    }

	init() {
		this.canvas = document.getElementById('pongCanvas');
		this.ctx = this.canvas.getContext('2d');
        this.ctx.canvas.width  = this.info.width;
        this.ctx.canvas.height = this.info.height;
        let dom_start = document.getElementById("start");
        dom_start.addEventListener("click", () => {
            $.ajax({
                url: '/start_game/',
                method: 'POST',
                data: {
                    "user": this.main.user,
                    "game_id": this.info.id
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
        // Handle keyboard input
        document.addEventListener('keydown', (event) => {
            switch (event.key) {
                case 'ArrowUp':
                    this.get_state("up");
                    break;
                case 'ArrowDown':
                    this.get_state("down");
                    break;
            }
            //console.log(event.key);
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

    get_state(to_do) {
        $.ajax({
            url: '/pong_state/',
            method: 'POST',
            data: {
                "user": this.main.user,
                "id": this.info.id,
                "do": to_do
            },
            success: (response) => {
                if (response.status === "ok")
                {
                    this.data = response;
                    this.draw();
                }
            },
            error: function(error) {
                console.error('Error: pong state POST fail', error.message);
            }
        });
    }

	draw() {
        //console.log("draw");
		// Clear the canvas
		this.ctx.clearRect(0, 0, this.info.data.width, this.info.data.height);

		// Draw paddles
		this.ctx.fillStyle = '#8b3a62';
        this.data.position.forEach((y, i) => {
		    this.ctx.fillRect(
                this.info.data.x[i],
                y,
                this.info.data.paddle_width,
                this.info.data.paddle_height);
        });

		// Draw this.ball
		this.ctx.beginPath();
		this.ctx.arc(this.data.ball.x, this.data.ball.y, this.info.data.ball_r, 0, Math.PI * 2);
		this.ctx.fillStyle = '#00ffcc';
		this.ctx.fill();
		this.ctx.closePath();
	}
}
