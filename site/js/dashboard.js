function convertirIndiceDirection(indice) {
    const pointsCardinaux = [
        "Nord",
        "Nord-Nord-Est",
        "Nord-Est",
        "Est-Nord-Est",
        "Est",
        "Est-Sud-Est",
        "Sud-Est",
        "Sud-Sud-Est",
        "Sud",
        "Sud-Sud-Ouest",
        "Sud-Ouest",
        "Ouest-Sud-Ouest",
        "Ouest",
        "Ouest-Nord-Ouest",
        "Nord-Ouest",
        "Nord-Nord-Ouest"
    ];

    return pointsCardinaux[indice];
}


function convertirIndiceUV(indice) {
    const intensitesUV = [
        "Faible",
        "Modéré",
        "Élevé",
        "Très élevé",
        "Extrême"
    ];

    return intensitesUV[indice];
}

function updateValues() {
    $.ajax({
        url: "../priseValeurs.php",
        dataType: 'json',
        success: function(result) {
            $("#vent").text(result.vitesse_vent+' Km/h');
            $("#pluie").text(result.valeur_pluie+' mm/m²');
            $("#termo").text(result.valeur_termometre+' °C');
            $("#ind_vent").text(convertirIndiceDirection(result.indice_tableau_direction_vent));
            $("#vis").text(result.visible+' lumen');
            $("#uv").text(convertirIndiceUV(result.valeur_ultraviolet));
        }
    });
}

updateValues();
setInterval(updateValues, 3000);

const TOGGLE = document.querySelector('button');
const HANDLE_TOGGLE = () => {
    TOGGLE.setAttribute('aria-pressed', TOGGLE.getAttribute('aria-pressed') === 'true' ? 'false' : 'true');
    document.body.classList.toggle('expanded', TOGGLE.matches('[aria-pressed="true"]'));
};
TOGGLE.addEventListener('click', HANDLE_TOGGLE);

const INPUT = document.querySelector('input');
const APPLY_TRANSFORM_BOX = () => {
    TOGGLE.classList.toggle('unset');
};
INPUT.addEventListener('change', APPLY_TRANSFORM_BOX);


