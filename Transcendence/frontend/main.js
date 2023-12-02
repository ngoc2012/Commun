import {Main} from './Main.js'
import {Game} from './Game.js'

var main = new Main();

document.addEventListener('DOMContentLoaded', function (event) {
    main.new_player();
    var game = new Game(main);
    main.load('/home', () => game.events());
});
