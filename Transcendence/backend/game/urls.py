# chat/urls.py
from django.urls import path

from . import views
from . import consumers

urlpatterns = [
    path("", views.index, name="index"),
    path('rooms/', consumers.RoomsConsumer.as_asgi()),
]

