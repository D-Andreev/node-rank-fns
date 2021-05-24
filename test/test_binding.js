const NodeRankFns = require('../dist/binding.js');
const assert = require('assert');

function testBasic() {
    const documents = [
        'this is a a sample',
        'this is another another example example example',
    ];
    const terms = ['example'];

    const instance = new NodeRankFns();
    const res = instance.tfIdf(documents, terms);
    console.log('Res: ', res);
    assert.deepEqual(res, [0, 0.12901285528456335]);
}

assert.doesNotThrow(testBasic, undefined, 'testBasic threw an exception');

console.log('Tests passed- everything looks OK!');