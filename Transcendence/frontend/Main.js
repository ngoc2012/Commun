export class Main
{
    user = "";
    name = "";
    id = -1;
    status = "";

    constructor()
    {
        this.dom_status = document.getElementById("status");
        this.dom_user_name = document.getElementById("user_name");
        this.dom_game = document.getElementById("game");
    }

    new_player() {
        $.ajax({
            url: '/new_player',
            method: 'GET',
            //headers: {'X-CSRFToken': csrftoken},
            success: (response) => {
                this.user = response.user;
                this.dom_user_name.innerHTML = this.user;
            },
            error: function(error) {
                console.error('Error: sending new player demand', error.message);
            }
        });
    }


   load(page, callback) {
        $.ajax({
            url: page + '/',
            method: 'GET',
            success: (html) => {
                //window.history.pushState({
                //    "user": this.user
                //}, page, page);
                this.dom_game.innerHTML = html;
                console.log("callback");
                if (typeof callback === 'function') {
                    callback();
                } else {
                    console.error('Callback is not a function.');
                }
            },
            error: function(error) {
                console.error('Error: pong GET fail', error.message);
            }
        });
    }
}