import json
from channels.generic.websocket import AsyncWebsocketConsumer

class PongConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.room_name = self.scope['url_route']['kwargs']['room_name']
        self.room_group_name = f"pong_{self.room_name}"

        # Join room group
        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name
        )

        await self.accept()

    async def disconnect(self, close_code):
        # Leave room group
        await self.channel_layer.group_discard(
            self.room_group_name,
            self.channel_name
        )

    async def receive(self, text_data):
        # Handle user input (if needed)
        pass

    async def update_state(self, event):
        state = event['state']

        # Send the updated game state back to all clients in the room
        await self.send(text_data=json.dumps({
            'state': state,
        }))

    async def player_join(self, event):
        # Notify all clients when a new player joins the room
        player_count = event['player_count']
        await self.send(text_data=json.dumps({
            'player_count': player_count,
        }))

