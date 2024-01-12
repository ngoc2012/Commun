from django.urls import path
from . import views
from .consumers import PongConsumer

app_name = 'pong'

urlpatterns = [
    path('', views.index, name='index'),
    path('room/(?P<room_name>\w+)/$', PongConsumer.as_asgi()),
]