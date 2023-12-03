import {Main} from './Main.js'
import {Game} from './Game.js'

var main = new Main();

document.addEventListener('DOMContentLoaded', function (event) {
    main.new_player();
    main.load('/home', () => main.game.events());
});
