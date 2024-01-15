from django.urls import path, re_path
from . import views
from .consumers import PongConsumer

app_name = 'pong'

urlpatterns = [
    path('', views.index, name='index'),
    path('set', views.set, name='set'),
]