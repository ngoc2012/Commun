export class Login
{
    constructor(m) {
        this.main = m;
    }
    
    events() {
        this.dom_login = document.querySelector("#login");
        this.dom_password = document.querySelector("#password");
        this.dom_log_in = document.querySelector("#log_in");
        this.dom_cancel = document.querySelector("#cancel");
        this.dom_log_in.addEventListener("click", () => this.login());
        this.dom_cancel.addEventListener("click", () => this.cancel());
    }

    login() {
        if (this.dom_login.value == '' || this.dom_password.value == '')
            return;
        console.log("login");
        $.ajax({
            url: '/log_in/',
            method: 'POST',
            data: {
                "login": this.dom_login.value,
                "password": this.dom_password.value,
            },
            success: (info) => {
                if ('error' in info)
                {
                    this.main.set_status(info.error)
                }
                else
                {
                    this.main.login = info.login;
                    this.main.name = info.name;
                    this.dom_user_name.textContent = info.name;
                }
            },
            error: (data) => this.main.set_status(data.error)
        });
    }

    cancel() {
        this.main.load('/lobby', () => this.main.lobby.events());
    }
}
