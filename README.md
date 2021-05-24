# node-rank-fns
<i>A native node addon with implementations of ranking functions.</i>

## Install 
`npm i node-rank-fns`

## Examples 

####1. TF-IDF ([Wiki](https://en.wikipedia.org/wiki/Tf%E2%80%93idf#Example_of_tf%E2%80%93idf))
```js
    const NodeRankFns = require('node-rank-fns');
    const assert = require('assert');

    function testBasic() {
        const documents = [
            'this is a a sample',
            'this is another another example example example',
        ];
        const terms = ['example'];
    
        const instance = new NodeRankFns();
        const res = instance.tfIdf(documents, terms);
        assert.deepEqual(res, [0, 0.12901285528456335]);
    }

    assert.doesNotThrow(testBasic, undefined, 'testBasic threw an exception');
```
Run example [here](https://github.com/D-Andreev/node-rank-fns/blob/master/test/test_binding.js)

####2. BM25 [Wiki](https://en.wikipedia.org/wiki/Okapi_BM25)