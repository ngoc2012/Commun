import {Main} from './Main.js'
import {Game} from './Game.js'

var main = new Main();

document.addEventListener('DOMContentLoaded', function (event) {
    //game.dom_online_players_list = dom_online_players_list;
    //game.dom_invitations = document.getElementById("invitations");
    //game.dom_status = dom_status;
    main.new_player();
    main.load('/home');
    var game = new Game();
});

