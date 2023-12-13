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
            self.room_group_name,
            {
                'type': 'game_update_state',
                'state': self.state,
            }
        )
        # Handle user input (if needed)
        pass

    async def update_state(self):
        # Send the updated game state back to all clients in the room
