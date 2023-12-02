import {Main} from './Main.js'
import {Game} from './Game.js'

var main = new Main();

document.addEventListener('DOMContentLoaded', function (event) {
    main.new_player();
    main.load('/home', get_game);
});

function get_game()
{
    var game = new Game(main);
    game.events();
    game.update();
}
