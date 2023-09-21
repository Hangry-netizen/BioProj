// Load the XLSX file using XMLHttpRequest
async function getData(file) {
    try {
        fetch(file).then(response => {
            return response.arrayBuffer();
        }).then(response => {
            console.log('file:', response);
        })
    } catch(e) {
        console.log(e)
    }
}

getData('./hb-short-sample.xlsx')