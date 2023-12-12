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
        this.dom_pong = document.querySelector("#pong");
        this.dom_pew = document.querySelector("#pew");
        this.dom_join = document.querySelector("#join");
        this.dom_rooms = document.getElementById("rooms");
        this.dom_pong.addEventListener("click", () => this.new_pong("pong"));
        this.dom_join.addEventListener("click", () => this.join());
        this.rooms_update();
    }

    reload() {
        this.main.load('/lobby', () => this.events());
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
            success: (info) => this.pong_game(info),
            error: (error) => this.main.set_status('Error: Can not join game')
        });
    }

    new_game(game) {
        $.ajax({
            url: '/new_game',
            method: 'POST',
            data: {
                "user": this.main.user,
                "game": game
            },
            success: (info) => this.pong_game(info),
            error: (error) => this.main.set_status('Error: Can not create game')
        });
    }

    pong_game(info) {
        this.game = new Pong(this.main, this, info);
        this.main.load('/pong', () => this.game.init());
    }

    rooms_update() {
        this.new_connection({
            name: "rooms update",
            socket: this.socket,
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
            param.socket.close();
            console.error('WebSocket ' + param.name + ' connection could not be established within the timeout.');
        }, CONNECTION_TIMEOUT);

        param.socket = new WebSocket(param.link);
        /*
        chatSocket.onmessage = function(e) {
            const data = JSON.parse(e.data);
            document.querySelector('#chat-log').value += (data.message + '\n');
        };

        chatSocket.onclose = function(e) {
            console.error('Chat socket closed unexpectedly');
        };

        document.querySelector('#chat-message-input').focus();
        document.querySelector('#chat-message-input').onkeyup = function(e) {
            if (e.key === 'Enter') {  // enter, return
                document.querySelector('#chat-message-submit').click();
            }
        };
         * */
        param.socket.addEventListener('open', (event) => {
            //socket.send(JSON.stringify({ message: 'Hello, server!' }));
            const data = JSON.parse(event.data);
            if ("open" in param.callback)
                param.callback.open(data);
        });
        param.socket.addEventListener('message', (event) => {
            const data = JSON.parse(event.data);
            if ("message" in param.callback)
                param.callback.message(data);
        });
        param.socket.addEventListener('error', (event) => {
            clearTimeout(timeout); // Clear the timeout if there's an error
            this.main.set_status = 'WebSocket ' + param.name + ' error:';
            if ("error" in param.callback)
                param.callback.error();
        });
        param.socket.addEventListener('close', (event) => {
            clearTimeout(timeout); // Clear the timeout if the connection is closed
            this.main.set_status = 'WebSocket ' + param.name + ' connection closed:';
            if ("close" in param.callback)
                param.callback.close();
        });
    }

}
