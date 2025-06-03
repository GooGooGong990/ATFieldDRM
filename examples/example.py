import random
import requests

def function(string):
    return random.randint(len(string), 999999)

var = input("> ")
print(f"안녕하세요 {function(var)}")

response = requests.get("https://google.com/")
print(f"google.com {response.status_code}")