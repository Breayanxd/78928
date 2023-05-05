var marker;
var markerArray = new Array();
var numMarker = 0;
var map = L.map('map').setView([19.590286923545793, -96.9424010224297], 13);
        L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
    maxZoom: 19,
    attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
}).addTo(map);

function addMarker() {
    const latitud = document.getElementById("idLatitud").value;
    const longitud = document.getElementById("idLongitud").value;
    const mensaje = document.getElementById("idMensaje").value;
    const coordenadas = document.getElementById("idCoordenadas");
    coordenadas.innerHTML = `Coordenadas Registradas: ${latitud},${longitud}`;
    marker = L.marker([latitud, longitud]).addTo(map);    
    numMarker++;
    marker.bindPopup(`<h5>Marker ${numMarker}:</h5><p>${mensaje}</p>`).openPopup();
    markerArray.push(marker);
    cleanInputs();
    console.log(markerArray)
}

function cleanInputs() {
    document.getElementById("idLatitud").value=""
    document.getElementById("idLongitud").value = "";
    document.getElementById("idMensaje").value = "";
}

function deleteMarker(){
    var valor = parseInt(document.getElementById("idMarcador").value)-1
    map.removeLayer(markerArray[valor])
    document.getElementById("idMarcador").value=""
}
