import {Game} from './Game.js'

export var game = new Game();

const dom_invite = document.querySelector("#invite");
const dom_online_players_list = document.getElementById("online_players_list");
const dom_status = document.getElementById("status");
const dom_invitations = document.getElementById("invitations");
const dom_accept_invitation = document.getElementById("accept_invitation");
const dom_cancel_invitation = document.getElementById("cancel_invitation");

document.addEventListener('DOMContentLoaded', function (event) {
    game.new_player();
    game.update();
});

dom_invite.addEventListener("click", function () {
    var online_players = get_players_selected();
    if (online_players.length === 2)
        game.invite(online_players);
});

dom_cancel_invitation.addEventListener("click", function () {
    if (game.id != -1)
        game.cancel_invitation();
});

function    get_players_selected()
{
    var options = dom_online_players_list && dom_online_players_list.options;
    var players_selected = [game.user];

    for (var i=0; i < options.length; i++) {
        if (options[i].selected) {
            players_selected.push(options[i].value);
        }
    }
    return (players_selected);
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
