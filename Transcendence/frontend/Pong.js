export class Pong
{
    update_time_interval = 50;
    data;
    canvas;
    ctx;

	constructor(g, i) {
        this.game = g;
        this.info = i;
    }

	init() {
		this.canvas = document.getElementById('pongCanvas');
		this.ctx = this.canvas.getContext('2d');
        this.ctx.canvas.width  = this.info.width;
        this.ctx.canvas.height = this.info.height;
        let dom_start = document.getElementById("start");
        dom_start.addEventListener("click", () => { set_state("start"); });
        document.addEventListener('keydown', (event) => {
            switch (event.key) {
                case 'ArrowUp':
                    this.set_state("up");
                    break;
                case 'ArrowDown':
                    this.set_state("down");
                    break;
            }
        });
	}

    set_state(e) {
        this.game.socket.send(JSON.stringify({ message: 'Hello, server!' }));
    }

    update_state(data) {
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
    
    end_game() {
        this.main.load('/home', () => main.lobby.events());
    }
}
