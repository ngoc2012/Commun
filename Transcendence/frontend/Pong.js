export class Pong
{
	height = 400;
	width = 800;
	paddleWidth = 10;
	paddleHeight = 60;

	constructor(m) {
        this.main = m;
    }

	init() {
		this.canvas = document.getElementById('pongCanvas');
		this.ctx = this.canvas.getContext('2d');
	}

	resetGame()
	{
		this.ball.x = this.canvas.width / 2;
		this.ball.y = this.canvas.height / 2;
		this.leftPaddle.y = this.canvas.height / 2 - this.paddleHeight / 2;
		this.rightPaddle.y = this.canvas.height / 2 - this.paddleHeight / 2;
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

		//requestAnimationFrame(() => this.draw());
	}
}
