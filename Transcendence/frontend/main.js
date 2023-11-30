class Game
{
    user_name = "";
}

export var game = new Game();
document.addEventListener('DOMContentLoaded', function (event) {
    update();
    new_player();
});

function update(){
    // do whatever you like here

    update_players_list();
    setTimeout(update, 2000);
}

const btn_invite = document.querySelector("#invite");
const dom_players_list = document.getElementById("players_list");

btn_invite.addEventListener("click", function () {
    var options = dom_players_list && dom_players_list.options;

    for (var i=0; i < options.length; i++)
    {
        if (options[i].selected)
        {
            console.log(options[i].value);
        }
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
function update_players_list(action) {
    // Make an AJAX request to send player action to the server
    $.ajax({
        url: '/players_list/',
        method: 'POST',
        data: { action: action },
        success: function(response) {
            // Handle server response if needed
            dom_players_list.innerHTML = "";
            //console.log(dom_players_list);
            var options = dom_players_list && dom_players_list.options;
            if (response.players.length > 0
                && response.players.length !== options.length)
            {
                console.log("Update players");
                response.players.forEach((element) => {
                    if (element !== game.user_name)
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
