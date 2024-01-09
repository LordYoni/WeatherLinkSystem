$(document).ready(function () {
    let data_temp = [];
    let graphique_temperature = new Chart(document.getElementById('graphique_temp').getContext('2d'), {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label: 'Température (°C)',
                borderColor: '#3498db',
                data: data_temp,
                fill: false,
            }]
        },
        options: {
            scales: {
                x: [{
                    type: 'time',
                    time: {
                        unit: 'hour',
                        displayFormats: {
                            hour: 'H:mm'
                        }
                    },
                    title: {
                        display: true,
                        text: 'Heures'
                    }
                }],
                y: {
                    type: 'linear',
                    position: 'left',
                    title: {
                        display: true,
                        text: 'Température (°C)'
                    }
                }
            }
        }
    });

    function updateGraphiqueTemp() {
        $.ajax({
            url: 'priseValeurs.php',
            dataType: 'json',
            success: function (data) {
                const now = new Date();
                const label = now.getHours();
                const valeur = parseFloat(data.valeur_termometre);
                data_temp.push(valeur);
                if (data_temp.length > 12) {
                    data_temp.shift();
                    graphique_temperature.data.labels.shift();
                }
                graphique_temperature.data.labels.push(label);
                graphique_temperature.data.datasets[0].data = data_temp;
                graphique_temperature.update();
            },
            error: function (error) {
                console.error('Erreur lors de la récupération des données Ajax:', error);
            }
        });
    }

    updateGraphiqueTemp();
    setInterval(updateGraphiqueTemp, 5000);





    let data_vent = [];
    let graphique_vent = new Chart(document.getElementById('graphique_vent').getContext('2d'), {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label: 'Vent (Km/h)',
                borderColor: '#3498db',
                data: data_vent,
                fill: false,
            }]
        },
        options: {
            scales: {
                x: [{
                    type: 'time',
                    time: {
                        unit: 'hour',
                        displayFormats: {
                            hour: 'H:mm'
                        }
                    },
                    title: {
                        display: true,
                        text: 'Heures'
                    }
                }],
                y: {
                    type: 'linear',
                    position: 'left',
                    title: {
                        display: true,
                        text: 'Vent (Km/h)'
                    }
                }
            }
        }
    });

    function updateGraphiqueVent() {
        $.ajax({
            url: 'priseValeurs.php',
            dataType: 'json',
            success: function (data) {
                const now = new Date();
                const label = now.getHours();
                const valeur = parseFloat(data.vitesse_vent);
                data_vent.push(valeur);
                if (data_vent.length > 12) {
                    data_vent.shift();
                    graphique_vent.data.labels.shift();
                }
                graphique_vent.data.labels.push(label);
                graphique_vent.data.datasets[0].data = data_vent;
                graphique_vent.update();
            },
            error: function (error) {
                console.error('Erreur lors de la récupération des données Ajax:', error);
            }
        });
    }

    updateGraphiqueVent();
    setInterval(updateGraphiqueVent, 5000);





    let data_pluie = [];
    let graphique_pluie = new Chart(document.getElementById('graphique_pluie').getContext('2d'), {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label: 'Pluie (mm/m²)',
                borderColor: '#3498db',
                data: data_pluie,
                fill: false,
            }]
        },
        options: {
            scales: {
                x: [{
                    type: 'time',
                    time: {
                        unit: 'hour',
                        displayFormats: {
                            hour: 'H:mm'
                        }
                    },
                    title: {
                        display: true,
                        text: 'Heures'
                    }
                }],
                y: {
                    type: 'linear',
                    position: 'left',
                    title: {
                        display: true,
                        text: 'Pluie (mm/m²)'
                    }
                }
            }
        }
    });

    function updateGraphiquePluie() {
        $.ajax({
            url: 'priseValeurs.php',
            dataType: 'json',
            success: function (data) {
                const now = new Date();
                const label = now.getHours();
                const valeur = parseFloat(data.valeur_pluie);
                data_pluie.push(valeur);
                if (data_pluie.length > 12) {
                    data_pluie.shift();
                    graphique_pluie.data.labels.shift();
                }
                graphique_pluie.data.labels.push(label);
                graphique_pluie.data.datasets[0].data = data_pluie;
                graphique_pluie.update();
            },
            error: function (error) {
                console.error('Erreur lors de la récupération des données Ajax:', error);
            }
        });
    }

    updateGraphiquePluie();
    setInterval(updateGraphiquePluie, 5000);





    let data_uv = [];
    let graphique_uv = new Chart(document.getElementById('graphique_uv').getContext('2d'), {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label: 'UV',
                borderColor: '#3498db',
                data: data_uv,
                fill: false,
            }]
        },
        options: {
            scales: {
                x: [{
                    type: 'time',
                    time: {
                        unit: 'hour',
                        displayFormats: {
                            hour: 'H:mm'
                        }
                    },
                    title: {
                        display: true,
                        text: 'Heures'
                    }
                }],
                y: {
                    type: 'linear',
                    position: 'left',
                    title: {
                        display: true,
                        text: 'UV'
                    }
                }
            }
        }
    });

    function updateGraphiqueUV() {
        $.ajax({
            url: 'priseValeurs.php',
            dataType: 'json',
            success: function (data) {
                const now = new Date();
                const label = now.getHours();
                const valeur = parseFloat(data.valeur_ultraviolet);
                data_uv.push(valeur);
                if (data_uv.length > 12) {
                    data_uv.shift();
                    graphique_uv.data.labels.shift();
                }
                graphique_uv.data.labels.push(label);
                graphique_uv.data.datasets[0].data = data_uv;
                graphique_uv.update();
            },
            error: function (error) {
                console.error('Erreur lors de la récupération des données Ajax:', error);
            }
        });
    }

    updateGraphiqueUV();
    setInterval(updateGraphiqueUV, 5000);





    let data_vis = [];
    let graphique_vis = new Chart(document.getElementById('graphique_vis').getContext('2d'), {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label: 'Visible',
                borderColor: '#3498db',
                data: data_vis,
                fill: false,
            }]
        },
        options: {
            scales: {
                x: [{
                    type: 'time',
                    time: {
                        unit: 'hour',
                        displayFormats: {
                            hour: 'H:mm'
                        }
                    },
                    title: {
                        display: true,
                        text: 'Heures'
                    }
                }],
                y: {
                    type: 'linear',
                    position: 'left',
                    title: {
                        display: true,
                        text: 'Visible (lumen)'
                    }
                }
            }
        }
    });

    function updateGraphiqueVis() {
        $.ajax({
            url: 'priseValeurs.php',
            dataType: 'json',
            success: function (data) {
                const now = new Date();
                const label = now.getHours();
                const valeur = parseFloat(data.visible);
                data_vis.push(valeur);
                if (data_vis.length > 12) {
                    data_vis.shift();
                    graphique_vis.data.labels.shift();
                }
                graphique_vis.data.labels.push(label);
                graphique_vis.data.datasets[0].data = data_vis;
                graphique_vis.update();
            },
            error: function (error) {
                console.error('Erreur lors de la récupération des données Ajax:', error);
            }
        });
    }

    updateGraphiqueVis();
    setInterval(updateGraphiqueVis, 5000);
});