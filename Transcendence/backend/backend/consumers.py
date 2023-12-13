import json
from channels.generic.websocket import AsyncWebsocketConsumer
from views import rooms

class GameConsumer(AsyncWebsocketConsumer):
    global rooms

    async def connect(self):
        self.group_name = "rooms"

        # Join group
        await self.channel_layer.group_add(
            self.group_name,
            self.channel_name
        )

    async def disconnect(self, close_code):
        # Leave room group
        await self.channel_layer.group_discard(
            self.group_name,
            self.channel_name
        )

    async def receive(self, text_data):
        #data = json.loads(text_data)
        #message = text_data_json['message']
        rooms.add(text_data)
        await self.channel_layer.group_send(
            self.group_name,
            {
                'type': 'update_rooms',
                'state': self.state,
            }
        )

    async def update_rooms(self, event):
        state = event['state']
        await self.send(text_data=json.dumps(rooms))
