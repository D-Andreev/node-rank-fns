function tfIdf(docs, terms) {
    const df = getDocumentFrequency(docs, terms);
    const scores = [];
    for (let i = 0; i < docs.length; i++) {
        const doc = docs[i];
        const words = doc.split(' ');
        const tf = getTermFrequency(words, terms);
        const idf = Math.log10(docs.length / df);
        scores.push(Math.abs(tf * idf));
    }

    return scores;
}

function getDocumentFrequency(docs, terms) {
    let df = 0;
    for (let i = 0; i < docs.length; i++) {
        const doc = docs[i];
        const words = doc.split(' ');
        let termExists = false;
        for (let j = 0; j < terms.length; j++) {
            const term = terms[j];
            for (let k = 0; k < words.length; k++) {
                const word = words[k];
                if (term === word) {
                    termExists = true;
                    break;
                }
            }
            if (termExists) break;
        }
        if (termExists) {
            df++;
        }
    }

    return df;
}

function getTermFrequency(document, terms) {
    let tfSum = 0;
    for (let i = 0; i < terms.length; i++) {
        const term = terms[i];
        let tf = 0;
        for (let j = 0; j < document.length; j++) {
            const word = document[j];
            if (term === word) {
                tf++;
            }
        }
        tfSum += tf / document.length;
    }

    return tfSum;
}

module.exports = tfIdf;