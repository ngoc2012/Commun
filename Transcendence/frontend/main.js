const game = new Game();
document.addEventListener('DOMContentLoaded', function (event) {
		game.draw();
		});

// Handle keyboard input
document.addEventListener('keydown', function (event) {
		switch (event.key) {
		case 'ArrowUp':
		game.rightPaddle.dy = -5;
		break;
		case 'ArrowDown':
		game.rightPaddle.dy = 5;
		break;
		case 'w':
		game.leftPaddle.dy = -5;
		break;
		case 's':
		game.leftPaddle.dy = 5;
		break;
		}
		});

document.addEventListener('keyup', function (event) {
		switch (event.key) {
		case 'ArrowUp':
		case 'ArrowDown':
		game.rightPaddle.dy = 0;
		break;
		case 'w':
		case 's':
		game.leftPaddle.dy = 0;
		break;
		}
		});

// AJAX Polling
function newplayer() {
    // Make an AJAX request to get the current game state
    $.ajax({
        url: '/new_player',
        method: 'POST',
        data: {},
        success: function(response) {
            // Handle server response if needed
        },
        error: function(error) {
            console.error('Error sending player action:', error);
        }
    });
}

// AJAX Polling
function pollGameState() {
    // Make an AJAX request to get the current game state
    $.ajax({
        url: '/api/state/',
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
        url: '/api/action/',
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
/*

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
