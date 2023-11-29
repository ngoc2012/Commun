import {Game} from "./game.js";

const game = new Game();
document.addEventListener('DOMContentLoaded', function (event) {
    update();
    new_player();
    game.draw();
});

function update(){
    // do whatever you like here

    update_players_list();
    setTimeout(update, 2000);
}


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
/*
function getCookie(name) {
    var cookieValue = null;
    if (document.cookie && document.cookie !== '') {
        var cookies = document.cookie.split(';');
        for (var i = 0; i < cookies.length; i++) {
            var cookie = cookies[i].trim();
            // Check if this cookie string begins with the name we want
            if (cookie.substring(0, name.length + 1) === (name + '=')) {
                cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
                break;
            }
        }
    }
    return cookieValue;
}
*/
// AJAX Polling
//var csrftoken = getCookie('csrftoken');
function new_player() {
    // Make an AJAX request to get the current game state
    $.ajax({
        url: '/new_player',
        method: 'GET',
	//headers: {'X-CSRFToken': csrftoken},
        success: function(response) {
            // Handle server response if needed
	    console.log(response);
	    game.user_name = response.name;
	    console.log(game.user_name);
        },
        error: function(error) {
            console.error('Error sending new player demand', error);
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

function update_players_list(action) {
    // Make an AJAX request to send player action to the server
    $.ajax({
        url: '/players_list/',
        method: 'POST',
        data: { action: action },
        success: function(response) {
            // Handle server response if needed
            //console.log(response);
            var dom_players_list = document.getElementById("players_list");
            //console.log(dom_players_list);
            response['players'].forEach((element) => {
                var option = document.createElement("option");
                option.value = element;
                option.text = element;
                dom_players_list.add(option);
            });
        },
        error: function(error) {
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
