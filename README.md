# node-rank-fns
<i>A native node addon with implementations of ranking functions.</i>

 * **[Install](#Install)**
 * **[TF-IDF](#TF-IDF)**
 * **[BM25](#BM25)**
 * **[Benchmarks](#Benchmarks)**
 * **[Contributing](#Contributing)**
 * **[Changelog](#Changelog)**
 * **[License](#License)**

<a name="Install"></a>
## Install 
- `npm i node-rank-fns`

## Examples 

<a name="TF-IDF"></a>
#### 1. TF-IDF ([Wiki](https://en.wikipedia.org/wiki/Tf%E2%80%93idf#Example_of_tf%E2%80%93idf))
Input files:
[documents.txt](https://github.com/D-Andreev/node-rank-fns/blob/master/test/documents.txt)
[terms.txt](https://github.com/D-Andreev/node-rank-fns/blob/master/test/terms.txt)

Run example [here](https://github.com/D-Andreev/node-rank-fns/blob/master/test/index.js)
```js
    const NodeRankFns = require('node-rank-fns');
    const assert = require('assert');

    function testTfIdf() {
        const instance = new NodeRankFns();
        const res = instance.tfIdf('./documents.txt', './terms.txt');
        assert.deepEqual(res, [0, 0.12901285528456335]);
    }

    assert.doesNotThrow(testBasic, undefined, 'testTfIdf threw an exception');
```

<a name="BM25"></a>
#### 2. BM25 ([Wiki](https://en.wikipedia.org/wiki/Okapi_BM25))
Input files:
[documents.txt](https://github.com/D-Andreev/node-rank-fns/blob/master/test/documents.txt)
[terms.txt](https://github.com/D-Andreev/node-rank-fns/blob/master/test/terms.txt)

Run example [here](https://github.com/D-Andreev/node-rank-fns/blob/master/test/index.js)
```js
    const NodeRankFns = require('node-rank-fns');
    const assert = require('assert');

    function testBM25() {
        const instance = new NodeRankFns();
        const res = instance.bm25('./documents.txt', './terms.txt');
        assert.deepEqual(res, [0, 0.07811157572119272]);
    }

    assert.doesNotThrow(testBM25, undefined, 'testBM25 threw an exception');
```

<a name="Benchmarks"></a>
## Benchmarks
`npm run benchmarks`

| TF-IDF           | Execution time   |
| ---------------- | ---------------- |
| vanillaJS*1000   | 5.063s           |
| nativeAddon*1000 | <b>767.641ms</b> |
| vanillaJS*1000   | 5.069s           |
| nativeAddon*1000 | <b>738.792ms</b> |

<a name="Contributing"></a>
## Contributing
Pull requests are welcome.

<a name="Changelog"></a>
## Changelog
For complete changelog [click here](https://github.com/D-Andreev/node-rank-fns/blob/master/CHANGELOG.md).

<a name="License"></a>
## License
MIT License

Copyright (c) 2021 Dimitar Andreev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
