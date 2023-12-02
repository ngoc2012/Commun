update_time_interval = 2000;

export function    game_events(game)
{
    dom_invite = document.querySelector("#invite");
    dom_accept_invitation = document.getElementById("accept_invitation");
    dom_cancel_invitation = document.getElementById("cancel_invitation");
    dom_online_players_list = document.getElementById("online_players_list");
    dom_invitations = document.getElementById("invitations");

    dom_invite.addEventListener("click", function () {
        var players = get_players_selected();
        //console.log(players);
        if (players.length === 2)
            game.invite(players);
    });

    dom_accept_invitation.addEventListener("click", function () {
        if (game.status !== "")
            return ;
        if (dom_invitations.selectedIndex !== -1) {
            game.accept_invitation(dom_invitations.options[dom_invitations.selectedIndex].value);
        }
    });

    dom_cancel_invitation.addEventListener("click", function () {
        if (dom_invitations.selectedIndex !== -1) {
            game.cancel_invitation(dom_invitations.options[dom_invitations.selectedIndex].value);
        }
    });
}



function    get_players_selected()
{
    var options = dom_online_players_list && dom_online_players_list.options;
    var players_selected = [game.user];

    for (var i=0; i < options.length; i++) {
        if (options[i].selected) {
            players_selected.push(options[i].value);
        }
    }
    return (players_selected);
}