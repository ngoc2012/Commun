import {Pong} from './Pong.js'

export class Lobby
{
    CONNECTION_TIMEOUT = 5000;

    constructor(m) {
        this.main = m;
        this.game = null;
        this.socket = -1;
    }
    
    events() {
        this.end_connection();
        this.dom_pong = document.querySelector("#pong");
        this.dom_pew = document.querySelector("#pew");
        this.dom_join = document.querySelector("#join");
        this.dom_rooms = document.getElementById("rooms");
        this.dom_pong.addEventListener("click", () => this.new_pong());
        this.dom_join.addEventListener("click", () => this.join());
        this.rooms_update();
    }

    return_lobby() {
        this.end_connection();
        this.main.load('/lobby', () => this.events());
    }

    join() {
        if (this.dom_rooms.selectedIndex === -1)
            return;
        this.end_connection();
        this.new_connection({
            name: "join",
            link: 'ws://127.0.0.1:8000/ws/join' + \
            '?user=' + this.main.id + \
            '&id=' this.dom_rooms.options[this.dom_rooms.selectedIndex].value,
            callback: {
                open: (info) => {
                    switch (info.game) {
                        case 'pong':
                            this.pong_game(info);
                            break;
                    }
                },
                message: this.game.update_state,
                close: this.return_lobby
            }
        });
    }

    new_pong() {
        this.end_connection();
        this.new_connection({
            name: "join",
            link: 'ws://127.0.0.1:8000/ws/new_room' + \
            '?user=' + this.main.id + \
            '&game=pong',
            callback: {
                open: this.pong_game,
                message: this.game.update_state,
                close: this.return_lobby
            }
        });
    }

    pong_game(info) {
        this.game = new Pong(this, info);
        this.main.load('/pong', () => this.game.init());
    }

    rooms_update() {
        this.new_connection({
            name: "rooms update",
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
                },
                error: this.rooms_update
            }
        });
    }

    new_connection(param)
    {
        const timeout = setTimeout(() => {
            this.socket.close();
            console.error('WebSocket ' + param.name + ' connection could not be established within the timeout.');
        }, CONNECTION_TIMEOUT);

        this.socket = new WebSocket(param.link);
        this.socket.addEventListener('open', (event) => {
            //socket.send(JSON.stringify({ message: 'Hello, server!' }));
            const data = JSON.parse(event.data);
            if ("open" in param.callback)
                param.callback.open(data);
        });
        this.socket.addEventListener('message', (event) => {
            const data = JSON.parse(event.data);
            if ("message" in param.callback)
                param.callback.message(data);
        });
        this.socket.addEventListener('error', (event) => {
            clearTimeout(timeout); // Clear the timeout if there's an error
            this.main.set_status = 'WebSocket ' + param.name + ' error:';
            if ("error" in param.callback)
                param.callback.error();
        });
        this.socket.addEventListener('close', (event) => {
            clearTimeout(timeout); // Clear the timeout if the connection is closed
            this.main.set_status = 'WebSocket ' + param.name + ' connection closed:';
            if ("close" in param.callback)
                param.callback.close();
        });
    }

    end_connection() {
        this.game = null;
        if (this.socket !== -1)
            this.socket.close();
        this.socket = -1;
    }
}
