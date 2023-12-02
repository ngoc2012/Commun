class Main
{
    user = "";
    name = "";
    id = -1;
    status = "";
    dom_status = document.getElementById("status");
    dom_user_name = document.getElementById("user_name");
    dom_game = document.getElementById("game");
    update_time_interval = 2000;

    new_player() {
        $.ajax({
            url: '/new_player',
            method: 'GET',
            //headers: {'X-CSRFToken': csrftoken},
            success: (response) => {
                this.user = response.user;
                this.dom_user_name = this.user;
            },
            error: function(error) {
                console.error('Error: sending new player demand', error.message);
            }
        });
    }


   load_page(page) {
        $.ajax({
            url: '/' + page + '/',
            method: 'GET',
            success: (html) => {
                window.history.pushState({
                    "user": this.user
                }, page, '/' + page);
                document.body.innerHTML = html;
            },
            error: function(error) {
                console.error('Error: pong GET fail', error.message);
            }
        });
    }
}
