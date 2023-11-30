import {Pong} from './Pong.js'

var pong = new Pong();

// Handle keyboard input
document.addEventListener('keydown', function (event) {
    switch (event.key) {
        case 'ArrowUp':
            pong.rightPaddle.dy = -5;
            break;
        case 'ArrowDown':
            pong.rightPaddle.dy = 5;
            break;
        case 'w':
            pong.leftPaddle.dy = -5;
            break;
        case 's':
            pong.leftPaddle.dy = 5;
            break;
    }
});

document.addEventListener('keyup', function (event) {
    switch (event.key) {
        case 'ArrowUp':
        case 'ArrowDown':
            pong.rightPaddle.dy = 0;
            break;
        case 'w':
        case 's':
            pong.leftPaddle.dy = 0;
            break;
    }
});
