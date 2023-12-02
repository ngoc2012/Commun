import {Game} from './Game.js'

var game = new Game();

const dom_invite = document.querySelector("#invite");
const dom_status = document.getElementById("status");
const dom_accept_invitation = document.getElementById("accept_invitation");
const dom_cancel_invitation = document.getElementById("cancel_invitation");
const dom_online_players_list = document.getElementById("online_players_list");
const dom_invitations = document.getElementById("invitations");

document.addEventListener('DOMContentLoaded', function (event) {
    //game.dom_online_players_list = dom_online_players_list;
    //game.dom_invitations = document.getElementById("invitations");
    //game.dom_status = dom_status;
    game.new_player();
    game.update();
});

dom_invite.addEventListener("click", function () {
    var players = get_players_selected();
    if (players.length === 2)
        game.invite(players);
});

dom_accept_invitation.addEventListener("click", function () {
    if (game.status !== "")
        return ;
    if (dom_invitations.selectedIndex !== -1) {
        game.accept_invitation(dom_invitations.options[dom_invitations.selectedIndex].value);
    }
});

dom_cancel_invitation.addEventListener("click", function () {
    if (dom_invitations.selectedIndex !== -1) {
        game.cancel_invitation(dom_invitations.options[dom_invitations.selectedIndex].value);
    }
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
