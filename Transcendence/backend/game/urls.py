# chat/urls.py
from django.urls import path

from . import views

urlpatterns = [
    path("new_game", views.new_game, name="new_game")
    path("delete", views.delete, name="delete")
]
