export class Game
{
    user = "";
    name = "";
    id = -1;
    status = "";
    dom_status = document.getElementById("status");
    dom_online_players_list = document.getElementById("online_players_list");
    dom_invitations = document.getElementById("invitations");

    update_time_interval = 2000;

    new_player() {
        $.ajax({
            url: '/new_player',
            method: 'GET',
            //headers: {'X-CSRFToken': csrftoken},
            success: function(response) {
                this.user = response.user;
            },
            error: function(error) {
                console.error('Error: sending new player demand', error);
            }
        });
    }

    update_online_players_list() {
        console.log("Update online");
        $.ajax({
            url: '/online_players_list/',
            method: 'POST',
            data: { "user": this.user },
            success: function(response) {
                var options = this.dom_online_players_list && this.dom_online_players_list.options;
                if (options && response.online_players_list.length !== options.length + 1) {
                    this.dom_online_players_list.innerHTML = "";
                    if (response.online_players_list.length > 0) {
                        response.online_players_list.forEach((element) => {
                            if (element !== this.user) {
                                var option = document.createElement("option");
                                option.value = element;
                                option.text = element;
                                this.dom_online_players_list.add(option);
                            }
                        });
                    }
                }
                var options_invitations = this.dom_invitations && this.dom_invitations.options;
                this.dom_invitations.innerHTML = "";
                if (options_invitations && response.user_info.invitations.length > 0) {
                    response.user_info.invitations.forEach((invitation) => {
                        var option = document.createElement("option");
                        option.value = invitation.id;
                        option.text = "" + invitation.id;
                        invitation.players.forEach((p) => {
                            option.text += " - " + p;
                        });
                        this.dom_invitations.add(option);
                    });
                }
            },
            error: function(error) {
            }
        });
    }

    update(){
        console.log("update :" + this.user);
        //if (this.status === "waiting")
        //    this.check_game_status;
        //else
        //    this.update_online_players_list;
        if (status !== "playing")
            setTimeout(function () {this.update();}, this.update_time_interval);
    }

    invite(players) {
        $.ajax({
            url: '/invite/',
            method: 'POST',
            data: {
                "host": this.user,
                "game": "pong",
                "players": players
            },
            success: function(response) {
                this.name = "pong";
                this.id = response.game_id;
                this.status = "waiting";
                this.dom_status.textContent = "New game " + this.name + " " + this.id + " created. Wait for players...";
                this.dom_online_players_list.innerHTML = "";
                this.dom_invitations.innerHTML = "";
            },
            error: function(error) {
            }
        });
    }

    accept_invitation(game_id) {
        $.ajax({
            url: '/accept_invitation/',
            method: 'POST',
            data: {
                "user": this.user,
                "game_id": game_id
            },
            success: function(response) {
                this.dom_status.textContent = "Game " + this.name + " " + this.id + " invitation is accepted by " + this.user;
                this.name = response.game;
                this.id = game_id;         
                this.status = "waiting";
            },
            error: function(error) {
                console.error('Error: accept invitation POST fail', error);
            }
        });
    }

    cancel_invitation(game_id) {
        $.ajax({
            url: '/cancel_invitation/',
            method: 'POST',
            data: {
                "user": this.user,
                "game_id": game_id
            },
            success: function(response) {
                this.dom_status.textContent = "Game " + this.name + " " + game_id + " invitation is canceled by " + this.user;
                if (this.id === game_id)
                {
                    this.name = "";
                    this.id = -1;         
                    this.status = "";
                }
            },
            error: function(error) {
                console.error('Error: cancel invitation POST fail', error);
            }
        });
    }

    check_game_status() {
        $.ajax({
            url: '/check_game_status/',
            method: 'POST',
            data: {
                "user": this.user,
                "game_id": this.id
            },
            success: function(response) {
                if (response === "canceled") {
                    this.dom_status.textContent = "Game " + this.name +" " + this.id + " is canceled";
                    this.name = "";
                    this.id = -1;         
                    this.status = "";
                }
                else if (response === "ready") {
                    this.dom_status.textContent = "Game " + this.name +" " + this.id + " is ready";
                }
            },
            error: function(error) {
                console.error('Error: check game GET fail', error);
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
