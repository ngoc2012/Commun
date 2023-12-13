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

    async def receive(self, data):
        await self.channel_layer.group_send(
            self.group_name,
            {
                'type': 'game_update_state',
                'state': self.state,
            }
        )

    async def game_update_state(self, event):
        # Handle the event when the game state is updated
        state = event['state']
        await self.send(text_data=json.dumps({
            'state': state,
        }))
