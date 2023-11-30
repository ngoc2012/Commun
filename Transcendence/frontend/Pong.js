export class Pong
{
	height = 400;
	width = 800;
	paddleWidth = 10;
	paddleHeight = 60;

	constructor()
	{
		this.canvas = document.getElementById('pongCanvas');
		this.ctx = this.canvas.getContext('2d');

		// Create the paddles
		this.leftPaddle = { x: 0, y: this.canvas.height / 2 - this.paddleHeight / 2, width: this.paddleWidth, height: this.paddleHeight, dy: 5 };
		this.rightPaddle = { x: this.canvas.width - this.paddleWidth, y: this.canvas.height / 2 - this.paddleHeight / 2, width: this.paddleWidth, height: this.paddleHeight, dy: 5 };

		// Create the this.ball
		this.ball = { x: this.canvas.width / 2, y: this.canvas.height / 2, radius: 10, dx: 5, dy: 5 };

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

		// Update this.ball position
		this.ball.x += this.ball.dx;
		this.ball.y += this.ball.dy;

		// Bounce off the top and bottom walls
		if (this.ball.y - this.ball.radius < 0 || this.ball.y + this.ball.radius > this.canvas.height)
		{
			this.ball.dy = -this.ball.dy;
		}
		// Bounce off left paddle
		if (
				this.ball.x - this.ball.radius < this.leftPaddle.x + this.leftPaddle.width &&
				this.ball.y > this.leftPaddle.y &&
				this.ball.y < this.leftPaddle.y + this.leftPaddle.height
		   )
		{
			this.ball.dx = -this.ball.dx;
		}

		// Bounce off right paddle
		if (
				this.ball.x + this.ball.radius > this.rightPaddle.x &&
				this.ball.y > this.rightPaddle.y &&
				this.ball.y < this.rightPaddle.y + this.rightPaddle.height
		   )
		{
			this.ball.dx = -this.ball.dx;
		}

		// Move paddles
		if (this.leftPaddle.y + this.leftPaddle.dy > 0 && this.leftPaddle.y + this.leftPaddle.dy < this.canvas.height - this.leftPaddle.height)
		{
			this.leftPaddle.y += this.leftPaddle.dy;
		}

		if (this.rightPaddle.y + this.rightPaddle.dy > 0 && this.rightPaddle.y + this.rightPaddle.dy < this.canvas.height - this.rightPaddle.height)
		{
			this.rightPaddle.y += this.rightPaddle.dy;
		}

		// Check for game over
		if (this.ball.x - this.ball.radius < 0 || this.ball.x + this.ball.radius > this.canvas.width)
		{
			this.resetGame();
		}

		//requestAnimationFrame(() => this.draw());
	}
}
