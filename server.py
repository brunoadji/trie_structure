from flask import Flask, request, jsonify
from flask_cors import CORS
import math

app = Flask(__name__)
cors = CORS(app)

@app.route("/receiver", methods=["POST"])
def postME():
    data = request.get_json()
    print(data)
    print(data["type"])

    if data["type"] == "transaction":
        res = "Transferindo de " + data["from"] + " para " + data["to"] + " a quantidade de " + data["amount"]
    
    if data["type"] == "create":
        res = "Criando a conta " + data["account"] + " com o saldo de " + data["amonut"]

    return jsonify(res)

if __name__ == "__main__":
    app.run()