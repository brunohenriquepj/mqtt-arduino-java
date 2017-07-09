$( document ).ready(function() {
  $(".button-collapse").sideNav();
  connect();
});

var stompClient = null;

function setConnected(connected) {
    if (connected) {
        Materialize.toast('Socket conectado!', 1000);
    } else {
        Materialize.toast('Socket desconectado!', 1000);
    }
}


function connect() {
    var socket = new SockJS('/server-iot-websocket');
    var topic = '/topic/area/' + idArea;

    stompClient = Stomp.over(socket);
    stompClient.debug = null; // Disabilita log do cliente
    stompClient.connect({}, function (frame) {
        setConnected(true);
        console.log('Connected');
        stompClient.subscribe(topic, function (data) {
            let dados = JSON.parse(data.body);
            alteraDadosDaArea(dados);
        });
    });
}


function disconnect() {
    if (stompClient != null) {
        stompClient.disconnect();
    }
    setConnected(false);
    console.log("Disconnected");
}


function alteraDadosDaArea(dados) {
    if (dados.identificador.startsWith('area/' + idArea + '/')) {
        if (dados.identificador.endsWith('/componente/1/temperatura/valor')) {
            alteraRangeTemperatura(dados);
        } else if (dados.identificador.endsWith('/componente/1/lampada/estado')) {
            alteraEstadoLampada('lampada1', dados);
        } else if (dados.identificador.endsWith('/componente/2/lampada/estado')) {
            alteraEstadoLampada('lampada2', dados);
        }
    }
}

const temperaturaClasses = [
    'fa-thermometer-empty',
    'fa-thermometer-quarter',
    'fa-thermometer-half',
    'fa-thermometer-three-quarters',
    'fa-thermometer-full'
];

function alteraRangeTemperatura(dados) {
    const valor = dados.valor;
    document.getElementById('temperatura-estado').innerHTML = valor;

    var indiceTemperaturaClasse = 0;
    if (valor > 0 && valor < 12) {
        indiceTemperaturaClasse = 1;
    } else if (valor >= 12 && valor < 24) {
        indiceTemperaturaClasse = 2;
    } else if (valor >= 24 && valor < 36) {
        indiceTemperaturaClasse = 3;
    } else if (valor >= 36) {
        indiceTemperaturaClasse = 4;
    }

    var i = 0;
    document.getElementById('temperatura-icone').classList.forEach(classe => {
    	if (classe.startsWith('fa-thermometer-')) {
    		document.getElementById('temperatura-icone').classList.remove(classe);
    		document.getElementById('temperatura-icone')
                    .classList
                    .add(temperaturaClasses[indiceTemperaturaClasse]);
    		console.log('index: ' + i);
    	}
    	i++;
    })
}

function alteraEstadoLampada(nomeLampada , dados) {
    const idIcone = nomeLampada + '-estado-icone';
    const idBadge = nomeLampada + '-estado-badge';
    const idBtn = nomeLampada + '-estado-btn';

    if (dados.valor == 1) {
        let elemento = document.getElementById(idBadge);
        elemento.innerHTML = 'LIGADA';
        let clases = elemento.classList;
        clases.remove('grey');
        clases.remove('lighten-2');
        clases.add('yellow');

        elemento = document.getElementById(idIcone);
        clases = elemento.classList;
        clases.remove('grey');
        clases.remove('lighten-2');
        clases.add('yellow');

        document.getElementById(idBtn).innerText = 'DESLIGAR';
    } else if (dados.valor == 0) {
        let elemento = document.getElementById(idBadge);
        elemento.innerHTML = 'APAGADA';
        let clases = elemento.classList;
        clases.remove('yellow');
        clases.add('grey');
        clases.add('lighten-2');

        elemento = document.getElementById(idIcone);
        clases = elemento.classList;
        clases.remove('yellow');
        clases.add('grey');
        clases.add('lighten-2');

        document.getElementById(idBtn).innerText = 'LIGAR';
    }
}


$(function () {
    $( "#lampada1-estado-btn" ).click(function() { enviaEstadoLampada('1', 'lampada1-estado-btn'); });
    $( "#lampada2-estado-btn" ).click(function() { enviaEstadoLampada('2', 'lampada2-estado-btn'); });
});


function enviaEstadoLampada(idComponente, id) {
    const elemento = document.getElementById(id);
    const estadoText = elemento.innerText;
    let estado = null;

    if (estadoText == 'LIGAR') {
        estado = 1;
    } else if (estadoText == 'DESLIGAR') {
        estado = 0;
    }
    const topico = '/app/area/' + idArea + '/lampada/' + idComponente + '/altera/estado';
    sendTopico(topico, estado);
}

function sendTopico(topico, conteudo) {
    let json = JSON.stringify({'identificador': topico, 'valor': conteudo});
    stompClient.send(topico, {}, json);
}
