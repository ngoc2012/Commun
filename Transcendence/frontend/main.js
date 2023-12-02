import {Main} from './Main.js'
import {Game} from './Game.js'

var main = new Main();

document.addEventListener('DOMContentLoaded', function (event) {
    main.new_player();
    main.load('/home');
    var game = new Game(main);
    document.addEventListener('DOMContentLoaded', function (event) {
        game.events();
        game.update();
    });
});

