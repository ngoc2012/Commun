import {Main} from './Main.js'
import {Game} from './Game.js'

var main = new Main();

document.addEventListener('DOMContentLoaded', function (event) {
    main.new_player();
    var game = new Game(main);
    main.load('/home', () => {
        console.log('load callback invoked');
        game.events();
    });
    //main.load('/home', game.events.bind(game));
});
