export class Lobby
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
            this.main.load('/pong', () => this.main.pong.init());
        });

        this.dom_join.addEventListener("click", () => {
            if (this.dom_rooms.selectedIndex !== -1) {
                this.join(this.dom_rooms.options[this.dom_rooms.selectedIndex].value);
            }
        });
        this.rooms_update();
    }

    rooms_update(game) {
        this.main.rooms_socket = new WebSocket('ws://127.0.0.1:8000/ws/rooms');
        // Event handler for when the connection is established
        //socket.addEventListener('open', (event) => {
        //    socket.send(JSON.stringify({ message: 'Hello, server!' }));
        //});

        // Event handler for incoming messages from the server
        socket.addEventListener('message', (event) => {
            const data = JSON.parse(event.data);
            //console.log('Received from server:', data.message);
            var options_rooms = this.dom_rooms && this.dom_rooms.options;
            this.dom_rooms.innerHTML = "";
            if (options_rooms && data.rooms && data.rooms.length > 0) {
                data.rooms.forEach((room) => {
                    var option = document.createElement("option");
                    option.value = room.id;
                    option.text = "" + room.id;
                    room.players.forEach((p) => {
                        option.text += " - " + p;
                    });
                    this.dom_rooms.add(option);
                });
            }
        });
    }

    join(game_id) {
        this.main.game_socket = new WebSocket('ws://example.com/ws/?user=2');
        // Event handler for when the connection is established
        //socket.addEventListener('open', (event) => {
        //    socket.send(JSON.stringify({ message: 'Hello, server!' }));
        //});
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
