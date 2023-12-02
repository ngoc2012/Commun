export class Game
{
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


/*
function getCookie(name) {
    var cookieValue = null;
    if (document.cookie && document.cookie !== '') {
        var cookies = document.cookie.split(';');
        for (var i = 0; i < cookies.length; i++) {
            var cookie = cookies[i].trim();
            // Check if this cookie string begins with the name we want
            if (cookie.substring(0, name.length + 1) === (name + '=')) {
                cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
                break;
            }
        }
    }
    return cookieValue;
}
*/
