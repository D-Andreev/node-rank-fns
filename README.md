# node-rank-fns
<i>A native node addon with implementations of ranking functions.</i>

## Install 
`npm i node-rank-fns`

## Examples 

####1. TF-IDF ([Wiki](https://en.wikipedia.org/wiki/Tf%E2%80%93idf#Example_of_tf%E2%80%93idf))
Input files:
[documents.txt](https://github.com/D-Andreev/node-rank-fns/blob/master/test/documents.txt)
[terms.txt](https://github.com/D-Andreev/node-rank-fns/blob/master/test/terms.txt)
```js
    const NodeRankFns = require('node-rank-fns');
    const assert = require('assert');

    function testBasic() {
        const instance = new NodeRankFns();
        const res = instance.tfIdf('./documents.txt', './terms.txt');
        assert.deepEqual(res, [0, 0.12901285528456335]);
    }

    assert.doesNotThrow(testBasic, undefined, 'testBasic threw an exception');
```
Run example [here](https://github.com/D-Andreev/node-rank-fns/blob/master/test/index.js)

####2. BM25 [Wiki](https://en.wikipedia.org/wiki/Okapi_BM25)


## Benchmarks
`npm run benchmarks`

| Implementation   | Execution time   |
| ---------------- | ---------------- |
| vanillaJS*1000   | 5.063s           |
| nativeAddon*1000 | <b>767.641ms</b> |
| vanillaJS*1000   | 5.069s           |
| nativeAddon*1000 | <b>738.792ms</b> |