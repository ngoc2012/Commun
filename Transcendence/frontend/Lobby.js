import {Pong} from './Pong.js'

export class Lobby
{
    connection_timeout = 5000;

    constructor(m) {
        this.main = m;
        this.game = null;
        this.info = null;
        this.rooms_socket = -1;
        this.game_socket = -1;
    }
    
    events() {
        this.main.game = null;
        this.dom_pong = document.querySelector("#pong");
        this.dom_pew = document.querySelector("#pew");
        this.dom_join = document.querySelector("#join");
        this.dom_rooms = document.getElementById("rooms");
        this.dom_pong.addEventListener("click", () => { this.new_pong(); });
        this.dom_join.addEventListener("click", () => { this.join(); });
        this.rooms_update();
    }

    join() {
        if (this.dom_rooms.selectedIndex === -1)
            return;
        this.end_game();
        new_connection({
            socket: this.main.game_socket,
            name: "join",
            link: 'ws://127.0.0.1:8000/ws/join' + \
            '?user=' + this.main.id + \
            '&id=' this.dom_rooms.options[this.dom_rooms.selectedIndex].value,
            callback: {
                open: (data) => {
                    switch (data.game) {
                        case 'pong':
                            this.pong_game(data);
                            break;
                    }
                }
            }
        });
    }

    new_pong() {
        this.end_game();
        new_connection({
            socket: this.main.game_socket,
            name: "join",
            link: 'ws://127.0.0.1:8000/ws/new_room' + \
            '?user=' + this.main.id + \
            '&game=pong',
            callback: {
                open: this.pong_game
            }
        });
    }

    pong_game(data) {
        this.main.game = new Pong(this, data);
        this.main.load('/pong', () => this.main.game.init());
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
        }, connection_timeout);

        param.socket = new WebSocket(param.link);
        param.socket.addEventListener('open', (event) => {
            //socket.send(JSON.stringify({ message: 'Hello, server!' }));
            const data = JSON.parse(event.data);
            param.callback.open(data);
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

    end_game() {
        this.main.game = null;
        if (this.main.game_socket !== -1)
            this.main.game_socket.close();
        this.main.game_socket = -1;
    }
}
