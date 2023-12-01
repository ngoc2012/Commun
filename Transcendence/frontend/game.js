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

const dom_invite = document.querySelector("#invite");
const dom_players_list = document.getElementById("players_list");
const dom_status = document.getElementById("status");
const dom_accept_invitation = document.getElementById("accept_invitation");
const dom_cancel_invitation = document.getElementById("cancel_invitation");

dom_cancel_invitation.addEventListener("click", function () {
    if (game.id != -1)
        cancel_invitation();
});

dom_invite.addEventListener("click", function () {
    var options = dom_players_list && dom_players_list.options;
    var players = [game.user];

    for (var i=0; i < options.length; i++) {
        if (options[i].selected) {
            players.push(options[i].value);
        }
    }
    if (players.length === 2)
        invite(players);
});

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
