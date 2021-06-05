const assert = require('assert');
const NodeRankFns = require('../dist/binding.js');
const rankFns = new NodeRankFns();
const documentsFilePath = './test/documents.txt';
const termsFilePath = './test/terms.txt';

function testTfIdf(cb) {
    rankFns.tfIdf(documentsFilePath, termsFilePath, (err, res) => {
        assert.equal(err, null);
        assert.deepEqual(res, [0, 0.12901285528456335]);
        cb();
    });
}

function testBM25(cb) {
    rankFns.bm25(documentsFilePath, termsFilePath, (err, res) => {
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