export class Game
{
    user = "";
    name = "";
    id = -1;
    status = "";

    update_time_interval = 2000;

    function new_player() {
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

    function update(){
        console.log("update :" + this.user);
        if (waiting)
            this.update_online_players_list();
        else
            this.check_game_status();
        if (status !== "playing")
            setTimeout(update, this.update_time_interval);
    }

    function update_online_players_list() {
        $.ajax({
            url: '/online_players_list',
            method: 'POST',
            data: { "user": this.user },
            success: function(response) {
                var options = dom_online_players_list && dom_online_players_list.options;
                if (response.online_players_list.length > 0
                    && response.online_players_list.length !== options.length + 1)
                {
                    //console.log(response.online_players_list.length);
                    dom_online_players_list.innerHTML = "";
                    response.online_players_list.forEach((element) => {
                        if (element !== this.user)
                        {
                            var option = document.createElement("option");
                            option.value = element;
                            option.text = element;
                            dom_online_players_list.add(option);
                        }
                    });
                }
            },
            error: function(error) {
            }
        });
    }

    function invite(players) {
        $.ajax({
            url: '/invite/',
            method: 'POST',
            data: {
                "host": this.user,
                "game": "pong",
                "players": players
            },
            success: function(response) {
                this.id = response.game_id;
                this.status = "waiting";
                this.name = "pong";
                dom_status.textContent = "New game " + this.name + " " + this.id + " created. Wait for players...";
                dom_online_players_list.innerHTML = "";
                response.online_players_list.forEach((element) => {
                    if (element !== this.user)
                    {
                        var option = document.createElement("option");
                        option.value = element;
                        option.text = element;
                        dom_online_players_list.add(option);
                    }
                });
            },
            error: function(error) {
            }
        });
    }

    function accept_invitation() {
        $.ajax({
            url: '/accept_invitation',
            method: 'POST',
            data: {
                "user": this.user,
                "game_id": this.id
            },
            success: function(response) {
                if (response.status === "accepted") {
                    dom_status.textContent = "Game " + this.name + " " + this.id + " invitation is accepted by " + this.user;
                    //this.name = "";
                    //this.id = -1;         
                    //this.waiting = false;
                }
                else
                    console.error(response.status);
            },
            error: function(error) {
                console.error('Error: accept invitation POST fail', error);
            }
        });
    }

    function cancel_invitation() {
        $.ajax({
            url: '/cancel_invitation',
            method: 'POST',
            data: {
                "user": this.user,
                "game_id": this.id
            },
            success: function(response) {
                if (response.status === "canceled")
                {
                    dom_status.textContent = "Game " + this.name + " " + this.id + " invitation is canceled by " + this.user;
                    this.name = "";
                    this.id = -1;         
                    this.waiting = false;
                }
                else
                    console.error(response.status);
            },
            error: function(error) {
                console.error('Error: cancel invitation POST fail', error);
            }
        });
    }

    function check_game_status() {
        $.ajax({
            url: '/check_game_status',
            method: 'POST',
            data: {
                "user": this.user,
                "game_id": this.id
            },
            success: function(response) {
                if (response === "canceled")
                {
                    dom_status.textContent = "Game " + this.name +" " + this.id + " is canceled";
                    this.name = "";
                    this.id = -1;         
                    this.waiting = false;
                }
                else
                    console.log(response.status);
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
