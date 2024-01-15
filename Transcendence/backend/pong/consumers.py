import json
from asgiref.sync import sync_to_async
from channels.generic.websocket import AsyncWebsocketConsumer
from game.models import RoomsModel, PlayersModel, PlayerRoomModel

from .data import pong_data

@sync_to_async
def get_room_data(players, room_id):
    room = RoomsModel.objects.get(id=room_id)
    return json.dumps({
        'ball': {'x': room.x, 'y':room.y},
        'players': [{'x': i.x, 'y': i.y} for i in players]
    })

class PongConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.room_id = self.scope['url_route']['kwargs']['room_id']
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
        room = RoomsModel.objects.get(id=room_id)
        i = 0
        dx = 1
        while i < 1000:
            await asyncio.sleep(1)
            self.state['ball_position']['x'] += pong_data['STEP']
            self.state['ball_position']['y'] += pong_data['STEP']
            # Notify all clients about the updated state
            await self.channel_layer.group_send(
                self.room_id,
                {
                    'type': 'group_data'
                }
            )
            i = i + 1
