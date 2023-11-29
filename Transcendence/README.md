# Transcendence

## The game

[The Mechanics of Pong](https://dooglz.github.io/set09121/pong2)

## Bootstrap toolkit

[Introduction](https://getbootstrap.com/docs/4.6/getting-started/introduction/)

## Another games

2 players shoots each others for 3 minutes.

Bullets speed increase over times.

1 shot each second.

## Django

### Api
```
Transcendence
├── backend
│   ├── __init__.py
│   ├── settings.py
│   ├── urls.py
│   └── wsgi.py
├── api
│   ├── __init__.py
│   └── pong
│       ├── __init__.py
│       ├── admin.py
│       ├── models.py
│       ├── tests.py
│       └── views.py
└── manage.py
```

[Api urls in subfolder](https://stackoverflow.com/questions/10313475/moving-django-apps-into-subfolder-and-url-py-error)

### Static files
If your JavaScript file is in a location that is not served by Django's development server, you need to make sure it's configured as a static file. In your Django project, you should have a folder named `static` where you store your static files (CSS, JavaScript, images, etc.). Ensure that your JavaScript file is placed in the appropriate static folder.

Update your `settings.py` to include your static files:

```
# settings.py
import os

# ...

STATIC_URL = '/static/'
STATICFILES_DIRS = [os.path.join(BASE_DIR, 'static')]

# ...
```

Add or update the `STATIC_ROOT` setting to point to a directory where you want to collect all your static files. For example:

```
# settings.py

# Your existing settings...

# Add or update this line
STATIC_ROOT = BASE_DIR / 'staticfiles'
```
Replace `'staticfiles'` with the desired directory path. `BASE_DIR` is a variable that represents the root directory of your Django project.

`STATICFILES_DIRS`: Specifies additional directories where Django should look for static files. These directories are searched when you use the `{% load static %}` template tag or the `static()` function in your templates. It is a list of strings representing paths.

```
# settings.py

STATICFILES_DIRS = [
    BASE_DIR / "myapp/static",
    "/var/www/static/",
]
```
`STATIC_ROOT`: Specifies the directory where Django will collect static files from all installed apps using the `collectstatic` management command. This is typically used in production to serve static files efficiently using a dedicated web server (e.g., Nginx or Apache).

```
# settings.py

STATIC_ROOT = BASE_DIR / 'staticfiles'
```

Make sure to run `python manage.py collectstatic` to collect static files into the `STATIC_ROOT` directory.

In your HTML file, you can then reference the JavaScript file using the `{% static %}` template tag:

```
<script src="{% static 'yourscript.js' %}"></script>
```

When Django runs in development mode (using `python manage.py runserver`), it can serve static files for you. `STATIC_URL` is the base URL under which these static files are accessible. For example, if `STATIC_URL` is set to `'/static/'`, a file named `style.css` in your `static` directory would be accessible at `http://localhost:8000/static/style.css`.


* Load the static template tag:

At the top of your template file (before using `{% static %}`), make sure you include the `{% load static %}` template tag.

```html
{% load static %}
<!DOCTYPE html>
<html>
...
```
## Javascript

[How to include a JavaScript file in another JavaScript file?](https://www.scaler.com/topics/javascript/import-js-file-in-js/)


