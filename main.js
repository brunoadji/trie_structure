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

function inserirDadosHistorico(contaOrigem, contaDestino, quantia) {
    let tabela = document.getElementById("tableHistoric");

    let novaLinha = tabela.insertRow();

    let colunaOrigem = novaLinha.insertCell();
    let colunaDestino = novaLinha.insertCell();
    let colunaQuantia = novaLinha.insertCell();

    colunaOrigem.textContent = contaOrigem;
    colunaDestino.textContent = contaDestino;
    colunaQuantia.textContent = quantia;
}

function showScreenTransaction() {
    document.getElementById("mainScreen").style.display = "none";
    document.getElementById("screenTransaction").style.display = "block";
}