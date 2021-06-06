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

function testBM25WithOptions(cb) {
    const rankFns = new NodeRankFns({k: 2, b: 0.5});
    rankFns.bm25(documentsFilePath, termsFilePath, (err, res) => {
        assert.equal(err, null);
        assert.deepEqual(res, [0, 0.04487832504164857]);
        cb();
    });
}

testTfIdf(() => {
    testBM25(() => {
        testBM25WithOptions(() => {
            console.log('Tests passed - everything looks OK!');
        });
    });
});