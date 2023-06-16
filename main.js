function showScreenCreateAccount() {
    document.getElementById("mainScreen").style.display = "none";
    document.getElementById("screenCreateAccount").style.display = "block";
}

function showScreenHistoric() {
    document.getElementById("mainScreen").style.display = "none";
    document.getElementById("screenHistoric").style.display = "block";
}

function backMainScreen() {
    cleanCreateAccount();
    cleanSendData();
    document.getElementById("screenCreateAccount").style.display = "none";
    document.getElementById("screenHistoric").style.display = "none";
    document.getElementById("screenTransaction").style.display = "none";
    document.getElementById("mainScreen").style.display = "block";
}

function cleanCreateAccount() {
    document.getElementById("inputCodeAccount").value = "";
    document.getElementById("inputAmountDisponible").value = "";
}

function cleanSendData() {
    document.getElementById("inputOriginAccount").value = "";
    document.getElementById("inputDestinyAccount").value = "";
    document.getElementById("inputAmount").value = "";
}

async function createAccount() {
    let type = "create"
    let account = document.getElementById("inputCodeAccount").value;
    let amount = document.getElementById("inputAmountDisponible").value;

    if(isNaN(amount)) 
        return alert("Erro: É necessário que a quantia na conta seja um número.");
    
    if(account == "" || amount == "")
        return alert("Erro: É necessário preencher todos os campos.");

    let res = await post({"type": type, "account": account, "amount": amount}, 'POST');
    console.log(res);
    backMainScreen();
}

async function sendTransaction() {
    let type = "transaction";
    let originAccount = document.getElementById("inputOriginAccount").value;
    let destinyAccount = document.getElementById("inputDestinyAccount").value;
    let amount = document.getElementById("inputAmount").value;

    if(isNaN(amount))
        return alert("Erro: É necessário que a quantia a ser transferida seja um número.");

    if(originAccount == "" || destinyAccount == "" || amount == "")
        return alert("Erro: É necessário preencher todos os campos.");

    let res = await post({"type": type, "from": originAccount, "to": destinyAccount, "amount": amount}, 'POST');
    console.log(res);
    backMainScreen();
}

function insertHistoric(originAccount, destinyAccount, amount) {
    let table = document.getElementById("tableHistoric");

    let newLine = table.insertRow();

    let originColumn = newLine.insertCell();
    let destinyColumn = newLine.insertCell();
    let amountColumn = newLine.insertCell();

    originColumn.textContent = originAccount;
    destinyColumn.textContent = destinyAccount;
    amountColumn.textContent = amount;
}

function showScreenTransaction() {
    document.getElementById("mainScreen").style.display = "none";
    document.getElementById("screenTransaction").style.display = "block";
}


async function post(data, method) {
    let res = "";
    await fetch("http://127.0.0.1:5000/receiver", 
        {
            method: method,
            headers: {
                'Content-type': 'application/json',
                'Accept': 'application/json'
            },

        body:JSON.stringify(data)}).then(res=>{
                if(res.ok){
                    return res.json();
                }else{
                    alert("something is wrong");
                }
            }).then(jsonResponse=>{
                res = jsonResponse;
            } 
            ).catch((err) => console.error(err));
    return res;
}