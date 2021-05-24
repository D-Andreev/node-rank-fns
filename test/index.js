const assert = require('assert');
const NodeRankFns = require('../dist/binding.js');

const documentsFilePath = './test/documents.txt';
const termsFilePath = './test/terms.txt';
const instance = new NodeRankFns();

function testTfIdf() {
    const res = instance.tfIdf(documentsFilePath, termsFilePath);
    console.log('TF-IDF: ', res);

    assert.deepEqual(res, [0, 0.12901285528456335]);
}
assert.doesNotThrow(testTfIdf, undefined, 'testBasic threw an exception');

function testBM25() {
    const res = instance.bm25(documentsFilePath, termsFilePath);
    console.log('BM25: ', res);

    assert.deepEqual(res, [0, 0.07811157572119272]);
}
assert.doesNotThrow(testBM25, undefined, 'testBM25 threw an exception');

console.log('Tests passed - everything looks OK!');