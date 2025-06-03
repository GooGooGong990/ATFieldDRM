<h1 align="center">ATFieldDRM</h1>

* ATFieldDRM is a Python obfuscator written in C.

## 사용 예시
```py
import random
import requests

def function(string):
    return random.randint(len(string), 999999)

var = input("> ")
print(f"안녕하세요 {function(var)}")

response = requests.get("https://google.com/")
print(f"google.com {response.status_code}")
```
```py
import ATFieldDRM
ATFieldDRM.run("Fu7BCg2F3CHYQ6XuJau/MIxCOWuDpBJZP7ihdGFnmg0a5ZEDCp+fJ9BCr6k71aQ0kkpiJan2Vwhqr7d0Zx/+SQ3i3wEQnNIh2EOl6CbV/jGZQ2Ns16QeRi30/iArVKlQRrqYb3WHnSGZEOHoJtGjKdQPdT+B/31YOLS8dDoLsoXqC1rg6hxpy1WpeW3SNfYmmlglfNe/GEZiq7NyOxCyQHWJwwAMgZM9ykjhvGjTsyyJSDhr0PgQTT718GhmGeAaRayeAhCemz/cA6LuJY70dPZdOXbNol9OaLq9b3UB9Ucc7NxFBIOZIMlCr/Itj6UpnVk+bPy1GEwvoPAp")
```

## 사용법
```
git clone https://github.com/GooGooGong990/ATFieldDRM.git
cd ATFieldDRM
```
### 난독화
```
python obfuscator.py PATH
```
### 빌드
```
cd src
python build_ext.py build_ext --key="Hello World!" --kek=0x22
```
> ⚠️ 윈도우 환경에서 C 확장 모듈을 빌드하려면 `Visual Studio Build Tools`가 필요합니다.

## 기여
* 진행중인 프로젝트로 기여 또는 PR를 환영합니다.

## 크레딧
* **sha256.c**
* **sha256.h**
> From https://github.com/B-Con/crypto-algorithms (Public Domain License) by @B-Con
