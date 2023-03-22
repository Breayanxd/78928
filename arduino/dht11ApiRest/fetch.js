const API_URL = "http://192.168.1.77/";

function cargarContenido(ruta) {
    if(ruta == "inicio"){
        contenedor.innerHTML = `PRÁCTICA API REST ESP32`;
    }else{
        const url = API_URL+ruta;
        console.log(url);
        fetch(url)
        .then(respuesta => respuesta.json())
        .then(data => {
            const contenedor = document.getElementById('contenedor');
            var fare;
            if(data['dato'] == "indiceCalor"){
                fare = parseFloat(data['valor']);
                valorF = (9/5*fare)+32;
                valorDef = valorF.toFixed(2); 
                contenedor.innerHTML = `El valor del índice de calor es de: ${data['valor']} C° - ${valorDef} F°`;
            }else{
                fare = parseFloat(data['valor']);
                valorF = (9/5*fare)+32;
                valorDef = valorF.toFixed(2);
                contenedor.innerHTML = `El valor de la ${data['dato']} es de: ${data['valor']} C° - ${valorDef} F°`;
            }
        })
        .catch(error=> console.log(error));
    }
}

function manejarCambiosUrl() {
    const url = location.hash.substr(1) || '/';
    cargarContenido(url);
}

window.addEventListener('hashchange', manejarCambiosUrl);