from flask import Flask, request, jsonify
from flask_cors import CORS
from ctypes import *

app = Flask(__name__)
cors = CORS(app)
trie = cdll.LoadLibrary("./trie.so")
trie.triInsert.argtypes = [c_char_p, c_float]
trie.triInsert.restype = c_int

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
    print(newAccount)
    var1 = newAccount.encode()
    print(var1)
    var2 = c_float(float(amount))
    print(var2)
    success = trie.triInsert(var1, var2)
    if(success == 1):
        return "Criando a conta \"" + newAccount + "\" com o saldo de " + amount
    return "Erro: Não foi possivel criar a conta"

if __name__ == "__main__":
    app.run()