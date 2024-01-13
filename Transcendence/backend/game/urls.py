# chat/urls.py
from django.urls import path

urlpatterns = [
    path("new", views.new_game, name="new_game")
]