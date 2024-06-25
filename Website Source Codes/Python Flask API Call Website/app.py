import requests
from flask import Flask, render_template, request

API_KEY = 'bd3359d1910f6d99b3d284848f9654baca040464'

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def main():
    if request.method == 'POST':
        if 'search' in request.args:
            ticker = request.args.get('search')
            response = requests.get(f'https://api.tiingo.com/tiingo/daily/{ticker}?token={API_KEY}')
            return response.json()
        elif 'iex' in request.args:
            ticker = request.args.get('iex')
            response = requests.get(f'https://api.tiingo.com/iex/{ticker}?token={API_KEY}')
            return response.json()
        else:
            return "Invalid request"
    return render_template('index.html')


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=5000)