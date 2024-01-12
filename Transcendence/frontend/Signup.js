export class Signup
{
    constructor(m) {
        this.main = m;
    }
    
    events() {
        this.main.set_status('')
        this.dom_login = document.querySelector("#login");
        this.dom_password = document.querySelector("#password");
        this.dom_name = document.querySelector("#name");
        this.dom_signup = document.querySelector("#signup");
        this.dom_cancel = document.querySelector("#cancel");
        this.dom_signup.addEventListener("click", () => this.signup());
        this.dom_cancel.addEventListener("click", () => this.cancel());
    }

    signup() {
        if (this.dom_login.value === ''
            || this.dom_password.value === ''
            || this.dom_name.value === '')
            return;
        console.log("signup");
        $.ajax({
            url: '/new_player/',
            method: 'POST',
            data: {
                "login": this.dom_login.value,
                "password": this.dom_password.value,
                "name": this.dom_name.value
            },
            success: (info) => {
                if (info.includes('Error'))
                {
                    this.main.set_status(info)
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
