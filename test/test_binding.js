const NodeRankFns = require('../dist/binding.js');
const assert = require('assert');

function testBasic() {
    const documents = ['100', '200', '300'];
    const terms = ['1'];

    const instance = new NodeRankFns();
    const res = instance.tfIdf(documents, terms);
    assert.deepEqual(res, documents);
}

assert.doesNotThrow(testBasic, undefined, 'testBasic threw an exception');

console.log('Tests passed- everything looks OK!');