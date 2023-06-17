from flask import Flask, request, jsonify
from flask_cors import CORS
from ctypes import *

app = Flask(__name__)
cors = CORS(app)

@app.route("/receiver", methods=["POST"])
def post():
    data = request.get_json()
    print(data)
    print(data["type"])

    if data["type"] == "transaction":
        res = transaction(data["from"], data["to"], data["amount"])

    if data["type"] == "create":
        res = create(data["account"], data["amount"])

    return jsonify(res)

def transaction(originAccount, destinyAccount, amount):
    return "Transferindo de \"" + originAccount + "\" para \"" + destinyAccount + "\" a quantia de " + amount

def create(newAccount, amount):
    return "Criando a conta \"" + newAccount + "\" com o saldo de " + amount

if __name__ == "__main__":
    app.run()