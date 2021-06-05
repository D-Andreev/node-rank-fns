const assert = require('assert');
const RecommenderSystem = require('../dist/binding.js');

const documentsFilePath = './test/documents.txt';
const termsFilePath = './test/terms.txt';
const instance = new RecommenderSystem();

function testTfIdf(cb) {
    instance.tfIdf(documentsFilePath, termsFilePath, (err, res) => {
        assert.equal(err, null);
        assert.deepEqual(res, [0, 0.12901285528456335]);
        cb();
    });
}

function testBM25(cb) {
    instance.bm25(documentsFilePath, termsFilePath, (err, res) => {
        assert.equal(err, null);
        assert.deepEqual(res, [0, 0.07811157572119272]);
        cb();
    });
}

testTfIdf(() => {
    testBM25(() => {
        console.log('Tests passed - everything looks OK!');
    });
});