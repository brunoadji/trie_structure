function showScreenCreateAccount() {
    document.getElementById("mainScreen").style.display = "none";
    document.getElementById("screenCreateAccount").style.display = "block";
}

function showScreenHistoric() {
    document.getElementById("mainScreen").style.display = "none";
    document.getElementById("screenHistoric").style.display = "block";
}

function backMainScreen() {
    limparCamposCriarConta();
    document.getElementById("screenCreateAccount").style.display = "none";
    document.getElementById("screenHistoric").style.display = "none";
    document.getElementById("screenTransaction").style.display = "none";
    document.getElementById("mainScreen").style.display = "block";
}

function limparCamposCriarConta() {
    document.getElementById("inputCodeAccount").value = "";
    document.getElementById("inputAmountDisponible").value = "";
}

function limparCamposEnviarDados() {
    document.getElementById("inputOriginAccount").value = "";
    document.getElementById("inputDestinyAccount").value = "";
    document.getElementById("inputAmount").value = "";
}

function createAccount() {
    backMainScreen();
}

function sendTransaction() {
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