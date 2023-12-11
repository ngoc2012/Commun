import {Main} from './Main.js'

var main = new Main();

document.addEventListener('DOMContentLoaded', () => {
    main.new_player();
    main.load('/home', () => main.game.events());
});
