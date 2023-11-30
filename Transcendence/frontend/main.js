class Game
{
    user = "";
    name = "";
    id = -1;
    waiting = false;
}

export var game = new Game();

document.addEventListener('DOMContentLoaded', function (event) {
    update();
    new_player();
});

function update(){
    // do whatever you like here
    if (waiting)
        update_players_list();
    else
        check_game_waiting();
    setTimeout(update, 2000);
}

const btn_invite = document.querySelector("#invite");
const dom_players_list = document.getElementById("players_list");
const dom_status = document.getElementById("status");

btn_invite.addEventListener("click", function () {
    var options = dom_players_list && dom_players_list.options;
    var players = [game.user];

    for (var i=0; i < options.length; i++)
    {
        if (options[i].selected)
        {
            players.push(options[i].value);
        }
    }
    if (players.length === 2)
        invite();
});

function invite(players) {
    // Make an AJAX request to send player action to the server
    $.ajax({
        url: '/invite/',
        method: 'POST',
        data: {
            "user": game.user,
            "game": "pong",
            "players": players
        },
        success: function(response) {
            game.id = response.game_id;
            game.waiting = true;
            game.name = "pong";
            dom_status.textContent = "waiting...";
        },
        error: function(error) {
        }
    });
}
// AJAX Polling
//var csrftoken = getCookie('csrftoken');
function cancel_game() {
    // Make an AJAX request to get the current game state
    $.ajax({
        url: '/check_game_waiting',
        method: 'GET',
        data: { "game_id": game.id },
        success: function(response) {
            if (response.status === "canceled")
            {
                dom_status.textContent = "Game " + game.name +" " + game.id + " is canceled";
                game.name = "";
                game.id = -1;         
                game.waiting = false;
            }
        },
        error: function(error) {
            console.error('Error sending new player demand', error);
        }
    });
}

function check_game_waiting() {
    // Make an AJAX request to get the current game state
    $.ajax({
        url: '/check_game_waiting',
        method: 'GET',
        data: { "game_id": game.id },
        success: function(response) {
            if (response.status === "canceled")
            {
                dom_status.textContent = "Game " + game.name +" " + game.id + " is canceled";
                game.name = "";
                game.id = -1;         
                game.waiting = false;
            }
        },
        error: function(error) {
            console.error('Error sending new player demand', error);
        }
    });
}

function new_player() {
    $.ajax({
        url: '/new_player',
        method: 'GET',
	//headers: {'X-CSRFToken': csrftoken},
        success: function(response) {
            game.user = response.user;
        },
        error: function(error) {
            console.error('Error sending new player demand', error);
        }
    });
}

// AJAX Polling
function update_players_list(action) {
    $.ajax({
        url: '/players_list/',
        method: 'POST',
        data: { "user": game.user },
        success: function(response) {
            var options = dom_players_list && dom_players_list.options;
            if (response.players.length > 0
                && response.players.length !== options.length + 1)
            {
                console.log(response.players.length);
                dom_players_list.innerHTML = "";
                response.players.forEach((element) => {
                    if (element !== game.user)
                    {
                        var option = document.createElement("option");
                        option.value = element;
                        option.text = element;
                        dom_players_list.add(option);
                    }
                });
            }
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
