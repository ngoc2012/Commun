import {Pong} from './Pong.js'

export class Lobby
{
    timeout_limit = 5000;

    constructor(m) {
        this.main = m;
    }
    
    events() {
        this.main.game = null;
        this.dom_pong = document.querySelector("#pong");
        this.dom_pew = document.querySelector("#pew");
        this.dom_join = document.querySelector("#join");
        this.dom_rooms = document.getElementById("rooms");
        this.dom_pong.addEventListener("click", () => {
            this.main.game = null;
            this.main.game_socket = -1;
            new_connection({
                socket: this.main.game_socket,
                name: "join",
                link: 'ws://127.0.0.1:8000/ws/new_room' + \
                '?user=' + this.main.id + \
                '&game=pong',
                callback: {
                    open: () => {
                        this.main.game = new Pong(this);
                        this.main.load('/pong', () => this.main.game.init());
                    }
                }
            });
        });

        this.dom_join.addEventListener("click", () => {
            this.join();
        });
        this.rooms_update();
    }

    end_game() {
        this.main.game = null;
        if (this.main.game_socket != -1)
            this.main.game_socket.close();
        this.main.game_socket = -1;
    }

    join() {
        this.main.game = null;
        this.main.game_socket = -1;
        if (this.dom_rooms.selectedIndex !== -1) {
            new_connection({
                socket: this.main.game_socket,
                name: "join",
                link: 'ws://127.0.0.1:8000/ws/join' + \
                '?user=' + this.main.id + \
                '&id=' this.dom_rooms.options[this.dom_rooms.selectedIndex].value,
                callback: {}
            });
        }
    }

    rooms_update() {
        new_connection({
            socket: this.main.rooms_socket,
            name: "join",
            link: 'ws://127.0.0.1:8000/ws/rooms',
            '?user=' + this.main.id + \
            '&id=' this.dom_rooms.options[this.dom_rooms.selectedIndex].value,
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
                }
            }
        });
    }

    new_connection(param)
    {
        const timeout = setTimeout(() => {
            socket.close();
            console.error('WebSocket ' + param.name + ' connection could not be established within the timeout.');
        }, timeout_limit);

        param.socket = new WebSocket(param.link);
        param.socket.addEventListener('open', (event) => {
            //socket.send(JSON.stringify({ message: 'Hello, server!' }));
            param.callback.open();
        });
        param.socket.addEventListener('message', (event) => {
            const data = JSON.parse(event.data);
            param.callback.message(data);
        });
        param.socket.addEventListener('error', (event) => {
            clearTimeout(timeout); // Clear the timeout if there's an error
            this.main.status = 'WebSocket ' + param.name + ' error:', event;
            param.callback.message(data);
        });
        param.socket.addEventListener('close', (event) => {
            clearTimeout(timeout); // Clear the timeout if the connection is closed
            console.log('WebSocket ' + param.name + ' connection closed:', event);
        });
    }
}
