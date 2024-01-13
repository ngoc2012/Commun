import {Pong} from './Pong.js'
import {new_connection} from './new_connection.js'

export class Lobby
{
    constructor(m) {
        this.main = m;
        this.socket = -1;
    }
    
    events() {
        this.game = null;
        this.dom_pong = document.querySelector("#pong");
        this.dom_pew = document.querySelector("#pew");
        this.dom_join = document.querySelector("#join");
        this.dom_rooms = document.getElementById("rooms");
        this.dom_pong.addEventListener("click", () => this.new_pong("pong"));
        this.dom_join.addEventListener("click", () => this.join());
        this.rooms_update();
    }

    join() {
        if (this.dom_rooms.selectedIndex === -1)
            return;
        $.ajax({
            url: '/join_game',
            method: 'POST',
            data: {
                "user": this.main.user,
                "id": this.dom_rooms.options[this.dom_rooms.selectedIndex].value
            },
            success: (info) => {
                switch (info.game) {
                    case 'pong':
                        this.pong_game(info);
                        break;
                }
            },
            error: (error) => this.main.set_status('Error: Can not join game')
        });
    }

    new_game(game) {
        this.main.set_status('');
        if (this.main.login === '')
        {
            this.main.set_status('Please login or sign up');
            return;
        }
        if (this.socket === -1)
        {
            this.main.set_status('No connection');
            return;
        }
        this.socket.send(JSON.stringify({
            'action': 'new',
            'name': 'Game name here',
            'game': game,
            'login': this.main.login
        }));
    }

    pong_game(info) {
        this.game = new Pong(this.main, this, info);
        this.main.load('/pong', () => this.game.init());
    }

    rooms_update() {
        this.main.set_status('');
        this.socket = new WebSocket(
            'ws://'
            + window.location.host
            + '/ws/game/rooms/'
        );

        this.socket.onmessage = function(e) {
            const data = JSON.parse(e.data);
            //document.querySelector('#chat-log').value += (data.message + '\n');
        };

        this.socket.onclose = function(e) {
            console.error('Chat socket closed unexpectedly');
        };
        /*
        new_connection({
            main: this.main,
            name: "rooms update",
            socket: this.socket,
            link: 'ws://'
                + window.location.host
                + '/ws/game/rooms/',
            callback: {
                message: (data) => {
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
                },
                error: this.rooms_update()
            }
        });
        */
    }
}
