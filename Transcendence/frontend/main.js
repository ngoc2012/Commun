import {Game} from './Game.js'

var game = new Game();

document.addEventListener('DOMContentLoaded', function (event) {
    //game.dom_online_players_list = dom_online_players_list;
    //game.dom_invitations = document.getElementById("invitations");
    //game.dom_status = dom_status;
    game.new_player();
    game.update();
});
