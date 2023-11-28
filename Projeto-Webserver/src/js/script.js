// Função para fazer a requisição AJAX
function getDataFromArduino() {
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            // Converte a resposta JSON em um objeto JavaScript
            var data = JSON.parse(this.responseText);
            // Exibe os dados na página
            document.getElementById("dadosArduino").innerHTML =
            "<p>Temperatura: " + data.A0 + "°C</p>" +
            "<p>Umidade: " + data.A1 + "%</p>" +
            "<p>Luminosidade: " + data.A2 + "lux</p>";
        }
    };
    
    // Realiza uma requisição POST para o servidor Arduino
    xhttp.open("POST", "http://192.168.0.100/", true);
    xhttp.send();
}

// Atualiza os dados automaticamente a cada 5 segundos
setInterval(getDataFromArduino, 5000);
// Chama a função para obter os dados pela primeira vez
getDataFromArduino();