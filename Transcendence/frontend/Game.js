import {game} from './main.js'

class Game
{
    user = "";
    name = "";
    id = -1;
    waiting = false;

export function invite(players) {
    $.ajax({
        url: '/invite/',
        method: 'POST',
        data: {
            "host": game.user,
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

export function accept_invitation() {
    $.ajax({
        url: '/accept_invitation',
        method: 'POST',
        data: {
            "user": game.user,
            "game_id": game.id
        },
        success: function(response) {
            if (response.status === "accepted") {
                dom_status.textContent = "Game " + game.name + " " + game.id + " invitation is accepted by " + game.user;
                //game.name = "";
                //game.id = -1;         
                //game.waiting = false;
            }
            else
                console.error(response.status);
        },
        error: function(error) {
            console.error('Error: accept invitation POST fail', error);
        }
    });
}

//var csrftoken = getCookie('csrftoken');
export function cancel_invitation() {
    $.ajax({
        url: '/cancel_invitation',
        method: 'POST',
        data: {
            "user": game.user,
            "game_id": game.id
        },
        success: function(response) {
            if (response.status === "canceled")
            {
                dom_status.textContent = "Game " + game.name + " " + game.id + " invitation is canceled by " + game.user;
                game.name = "";
                game.id = -1;         
                game.waiting = false;
            }
            else
                console.error(response.status);
        },
        error: function(error) {
            console.error('Error: cancel invitation POST fail', error);
        }
    });
}

export function check_game_status() {
    $.ajax({
        url: '/check_game_status',
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
            else
                console.log(response.status);
        },
        error: function(error) {
            console.error('Error: check game GET fail', error);
        }
    });
}

export function new_player() {
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

export function update_players_list() {
    $.ajax({
        url: '/players_list',
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
}


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
