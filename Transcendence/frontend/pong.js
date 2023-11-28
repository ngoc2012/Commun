class Game
{
#height = 400;
#width = 800;
#paddleWidth = 10;
#paddleHeight = 60;
#canvas = document.getElementById('pongCanvas');
#leftPaddle;
#rightPaddle;
#ctx;

	resetGame()
	{
		this.ball.x = this.canvas.width / 2;
		this.ball.y = this.canvas.height / 2;
		this.leftPaddle.y = this.canvas.height / 2 - this.paddleHeight / 2;
		this.rightPaddle.y = this.canvas.height / 2 - this.paddleHeight / 2;
	}

	draw() {
		// Clear the canvas
		ctx.clearRect(0, 0, canvas.width, canvas.height);

		// Draw paddles
		ctx.fillStyle = '#8b3a62';
		ctx.fillRect(leftPaddle.x, leftPaddle.y, leftPaddle.width, leftPaddle.height);
		ctx.fillRect(rightPaddle.x, rightPaddle.y, rightPaddle.width, rightPaddle.height);

		// Draw ball
		ctx.beginPath();
		ctx.arc(ball.x, ball.y, ball.radius, 0, Math.PI * 2);
		ctx.fillStyle = '#00ffcc';
		ctx.fill();
		ctx.closePath();

		// Update ball position
		ball.x += ball.dx;
		ball.y += ball.dy;

		// Bounce off the top and bottom walls
		if (ball.y - ball.radius < 0 || ball.y + ball.radius > canvas.height) {
			ball.dy = -ball.dy;
		}
	start()
	{
		this.ctx = this.canvas.getContext('2d');
		// Create the paddles
		this.leftPaddle = { x: 0, y: this.canvas.height / 2 - this.paddleHeight / 2, width: this.paddleWidth, height: this.paddleHeight, dy: 5 };
		this.rightPaddle = { x: this.canvas.width - this.paddleWidth, y: this.canvas.height / 2 - this.paddleHeight / 2, width: this.paddleWidth, height: this.paddleHeight, dy: 5 };

		// Create the ball
		const ball = { x: this.canvas.width / 2, y: this.canvas.height / 2, radius: 10, dx: 5, dy: 5 };


		// Bounce off left paddle
		if (
				ball.x - ball.radius < leftPaddle.x + leftPaddle.width &&
				ball.y > leftPaddle.y &&
				ball.y < leftPaddle.y + leftPaddle.height
		   ) {
			ball.dx = -ball.dx;
		}

		// Bounce off right paddle
		if (
				ball.x + ball.radius > rightPaddle.x &&
				ball.y > rightPaddle.y &&
				ball.y < rightPaddle.y + rightPaddle.height
		   ) {
			ball.dx = -ball.dx;
		}

		// Move paddles
		if (leftPaddle.y + leftPaddle.dy > 0 && leftPaddle.y + leftPaddle.dy < canvas.height - leftPaddle.height) {
			leftPaddle.y += leftPaddle.dy;
		}

		if (rightPaddle.y + rightPaddle.dy > 0 && rightPaddle.y + rightPaddle.dy < canvas.height - rightPaddle.height) {
			rightPaddle.y += rightPaddle.dy;
		}

		// Check for game over
		if (ball.x - ball.radius < 0 || ball.x + ball.radius > canvas.width) {
			resetGame();
		}

		requestAnimationFrame(draw);
		}


		// Handle keyboard input
		document.addEventListener('keydown', function (event) {
				switch (event.key) {
				case 'ArrowUp':
				rightPaddle.dy = -5;
				break;
				case 'ArrowDown':
				rightPaddle.dy = 5;
				break;
				case 'w':
				leftPaddle.dy = -5;
				break;
				case 's':
				leftPaddle.dy = 5;
				break;
				}
				});

		document.addEventListener('keyup', function (event) {
				switch (event.key) {
				case 'ArrowUp':
				case 'ArrowDown':
				rightPaddle.dy = 0;
				break;
				case 'w':
				case 's':
				leftPaddle.dy = 0;
				break;
				}
				});

		// Start the game loop
		draw();
	}
}


game = new Game();

document.addEventListener('DOMContentLoaded', game.start());

/*
// AJAX Polling
function pollGameState() {
    // Make an AJAX request to get the current game state
    $.ajax({
        url: '/api/game-state/',
        method: 'GET',
        success: function(data) {
            // Update game elements based on data received from the server
            updateGame(data);
        },
        error: function(error) {
            console.error('Error fetching game state:', error);
        }
    });
}

// Send player actions to the server
function sendAction(action) {
    // Make an AJAX request to send player action to the server
    $.ajax({
        url: '/api/send-action/',
        method: 'POST',
        data: { action: action },
        success: function(response) {
            // Handle server response if needed
        },
        error: function(error) {
            console.error('Error sending player action:', error);
        }
    });
}

// Example: Move paddle up
document.addEventListener('keydown', function (event) {
    if (event.key === 'ArrowUp') {
        sendAction('move_up');
    }
});

// Example: Move paddle down
document.addEventListener('keydown', function (event) {
    if (event.key === 'ArrowDown') {
        sendAction('move_down');
    }
});

// Update game elements based on data received from the server
function updateGame(data) {
    // Update game elements (e.g., paddle and ball positions) based on data
}

// Poll for game state every 100 milliseconds (adjust as needed)
setInterval(pollGameState, 100);
*/
