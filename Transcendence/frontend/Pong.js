export class Pong
{
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
        let dom_quit = document.getElementById("quit");
        dom_start.addEventListener("click", () => this.set_state("start"));
        dom_quit.addEventListener("click", () => this.quit());
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
        if (this.game.socket !== -1)
            this.game.socket.send(JSON.stringify({ 'do': e }));
    }

    update_state(data) {
        this.data = data;
        if (this.game.socket !== -1)
            this.game.socket.send("got");
    }

	draw() {
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
