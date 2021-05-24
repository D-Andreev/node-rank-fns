const assert = require('assert');
const NodeRankFns = require('../dist/binding.js');

const documentsFilePath = './test/documents.txt';
const termsFilePath = './test/terms.txt';

function testTfIdf() {
    const instance = new NodeRankFns();
    const res = instance.tfIdf(documentsFilePath, termsFilePath);
    console.log('Res: ', res);

    assert.deepEqual(res, [0, 0.12901285528456335]);
}

assert.doesNotThrow(testTfIdf, undefined, 'testBasic threw an exception');
console.log('Tests passed - everything looks OK!');