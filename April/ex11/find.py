import requests

pokemon_name = input("Enter the name of a Pokemon: ")

pokemon_name0 = pokemon_name.lower()
pokemon_name1 = pokemon_name0.capitalize()

url = f"https://pokeapi.co/api/v2/pokemon/{pokemon_name0}/"

response = requests.get(url)

if response.status_code == 200:
    pokemon_data = response.json()
    print(f"Name: {pokemon_name1}")
    print("Abilities:")
    for ability in pokemon_data['abilities']:
        a = ability['ability']['name'].capitalize()
        print(f"- {a}")
else:
    print(f"Could not find information for {pokemon_name}")

