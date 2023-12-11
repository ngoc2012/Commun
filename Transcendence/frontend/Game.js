export class Game
{
    update_time_interval = 2000;

    constructor(m) {
        this.main = m;
    }
    
    events() {
        this.dom_pong = document.querySelector("#pong");
        this.dom_join = document.querySelector("#join");
        this.dom_rooms = document.getElementById("rooms");
        this.dom_pong.addEventListener("click", () => {
            this.new_pong_room();
        });

        this.dom_join.addEventListener("click", () => {
            if (this.dom_rooms.selectedIndex !== -1) {
                this.join(this.dom_rooms.options[this.dom_rooms.selectedIndex].value);
            }
        });
        this.rooms_update();
    }

    rooms_update(game) {
        //console.log("Update online");
        $.ajax({
            url: '/rooms_updates/',
            method: 'POST',
            data: { "user": this.main.user },
            success: (response) => {
                var options_rooms = this.dom_rooms && this.dom_rooms.options;
                this.dom_rooms.innerHTML = "";
                if (options_rooms && response.rooms
                    && response.rooms.length > 0) {
                    response.rooms.forEach((room) => {
                        var option = document.createElement("option");
                        option.value = room.id;
                        option.text = "" + room.id;
                        room.players.forEach((p) => {
                            option.text += " - " + p;
                        });
                        this.dom_rooms.add(option);
                    });
                }
            },
            error: function(error) {
                //console.error('Error: online players list POST fail', error.message);
            }
        });
    }

    new_pong_room() {
        //console.log(players);
        $.ajax({
            url: '/invite/',
            method: 'POST',
            data: {
                "host": this.main.user,
                "game": "pong",
            },
            success: (response) => {
                this.main.name = "pong";
                this.main.id = response.id;
                this.main.status = "waiting";
                this.main.game_info = response;
                this.main.dom_status.textContent = "New game " + this.main.name + " " + this.main.id + " created. Wait for players...";
                //this.dom_online_players_list.innerHTML = "";
                //this.dom_invitations.innerHTML = "";
            },
            error: function(error) {
                console.error('Error: invite POST fail', error.message);
            }
        });
    }

    join(game_id) {
        $.ajax({
            url: '/accept_invitation/',
            method: 'POST',
            data: {
                "user": this.main.user,
                "game_id": game_id
            },
            success: (response) => {
                this.main.dom_status.textContent = "Game " + this.main.name + " " + this.main.id + " invitation is accepted by " + this.main.user;
                this.main.name = response.game;
                this.main.id = game_id;         
                this.main.status = "waiting";
                this.main.game_info = response;
            },
            error: function(error) {
                console.error('Error: accept invitation POST fail', error.message);
            }
        });
    }
}
