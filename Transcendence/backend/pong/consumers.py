import json
from asgiref.sync import sync_to_async
from channels.generic.websocket import AsyncWebsocketConsumer
from game.models import RoomsModel, PlayerRoomModel

import asyncio

from .data import pong_data

@sync_to_async
def get_room_data(players, room_id):
    room = RoomsModel.objects.get(id=room_id)
    return json.dumps({
        'ball': {'x': room.x, 'y':room.y},
        'players': [{'x': i.x, 'y': i.y} for i in players]
    })

@sync_to_async
def get_room_players(consumer):
    room = RoomsModel.objects.get(id=self.room_id)
        room.started = True
        room.save()
        players0 = PlayerRoomModel.objects.filter(room=self.room_id, side=0)
        players1 = PlayerRoomModel.objects.filter(room=self.room_id, side=1)
class PongConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.room_id = self.scope['url_route']['kwargs']['room_id']
        self.room = None
        self.players0 = None
        self.players1 = None
        # Join room group
        await self.channel_layer.group_add(
            self.room_id,
            self.channel_name
        )
        await self.accept()
        await self.channel_layer.group_send(
            self.room_id,
            {
                'type': 'group_data'
            }
        )
        # Start a loop to continuously update the game state
        #await self.game_loop()

    async def disconnect(self, close_code):
        await self.channel_layer.group_discard(
            self.room_id,
            self.channel_name
        )

    async def receive(self, text_data):
        if text_data == 'start':
            await self.game_loop()
        else:
            await self.channel_layer.group_send(
                self.room_id,
                {
                    'type': 'group_data'
                }
            )
    
    async def group_data(self, event):
        players = PlayerRoomModel.objects.filter(room=self.room_id)
        room_data = await get_room_data(players, self.room_id)
        await self.send(text_data=room_data)
    
    async def game_loop(self):
        
        i = 0
        dx = 1
        dy = 1
        while i < 100:
            await asyncio.sleep(1)
            room.x += dx * pong_data['DX']
            room.y += dy * pong_data['DY']
            if room.y + pong_data['RADIUS'] >= pong_data['HEIGHT'] or room.y - pong_data['RADIUS'] <= 0:
                dy *= -1
            if dx == -1:
                for p in players0:
                    if room.x - pong_data['RADIUS'] == p.x + pong_data['PADDLE_WIDTH'] and room.y >= p.y and room.y <= p.y + pong_data['PADDLE_HEIGHT']:
                        dx = 1
            else:
                for p in players1:
                    if room.x + pong_data['RADIUS'] == p.x and room.y >= p.y and room.y <= p.y + pong_data['PADDLE_HEIGHT']:
                        dx = -1
            room.save()
            if room.x <= 0 or room.x >= pong_data['WIDTH']:
                room.x = room.server.x + pong_data['RADIUS']
                room.y = room.server.y
                room.started = False
                room.save()
                return
            await self.channel_layer.group_send(
                self.room_id,
                {
                    'type': 'group_data'
                }
            )
            i += 1
