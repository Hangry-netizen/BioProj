let bLength = 0;
let tLength = 0;

// Convert CSV text content into 2D arrays
function csvToArray(csvContent) {
    // Split the CSV text into lines
    const lines = csvContent.split('\n');
    const dataArray = [];

    for (let i = 0; i < lines.length; i++) {
        // Split each line into an array using a comma delimiter
        const row = lines[i].split(',');
        // Add the array representing a row to the result array
        dataArray.push(row);
    }

    return dataArray;
}

function drawVisualisation(data, startPoint) {
    let matches = document.getElementById("matches-lines");
    let base = document.getElementById("base-rectangle");
    let target = document.getElementById("target-rectangle");
    let basePoints, targetPoints,lines = '';

    for (let i = startPoint; i < data.length-1; i++) {
        // Record the start and end pixels of match at the base and target genomes
        let bStart = (data[i][1]) / (bLength);
        let tStart = (data[i][4]) / (tLength);
        let bEnd = ((data[i][1]) + (data[i][2])) / (bLength);
        let tEnd = ((data[i][4]) + (data[i][2])) / (tLength);
        console.log(bStart, tStart, bEnd, tEnd);

        // Draw points of begin and end of match on base rectangle
        basePoints += `<line x1=${bStart} y1=0 x2=${bStart} y2=30 stroke='red' stroke-width='1'/>`
        basePoints += `<line x1=${bEnd} y1=0 x2=${bEnd} y2=30 stroke='green' stroke-width='1'/>`

        // Draw points of begin and end of match on target rectangle
        targetPoints += `<line x1=${tStart} y1=0 x2=${tStart} y2=30 stroke='red' stroke-width='1'/>`
        targetPoints += `<line x1=${tEnd} y1=0 x2=${tEnd} y2=30 stroke='green' stroke-width='1'/>`

        // Draw matches between base and target as lines
        lines += `<line x1=${bStart} y1=0 x2=${tStart} y2=500 stroke='orange' stroke-width='1'/>`
        lines += `<line x1=${bEnd} y1=0 x2=${tEnd} y2=500 stroke='orange' stroke-width='1'/>`
    }

    // Draw points and lines
    base.innerHTML = basePoints;
    matches.innerHTML = lines;
    target.innerHTML = targetPoints;
}

// Fetch the CSV file and draw visualisation
async function getData(file) {
    try {
        // Use the fetch API to request the CSV file
        fetch(file)
            // Convert the response to text
            .then(response => response.text())
            .then(csvContent => {
                // Convert CSV text to array of arrays
                let dataArray = csvToArray(csvContent);
                let startPoint = 0;

                console.log(dataArray[0].length);
                if (dataArray[0].length ) {
                    // Calculate the number of chromosomes represented per pixel in the base and target genomes
                    bLength = dataArray[0][0] / 1200;
                    tLength = dataArray[0][1] / 1200;
                    startPoint = 1;
                }

                // Draw visualisation of data
                if (bLength && tLength) {
                    drawVisualisation(dataArray, startPoint);
                }
        })
    } catch(e) {
        // Handle errors if the fetch operation fails
        console.log("Error fetching CSV file:", e);
    }
}

// Specify the path of the CSV file to be loaded
for (let i = 0; i < 1; i++) {
    getData(`sample100.csv`);
}