# recommender-system
<i>A native node addon with implementations of various utility functions commonly used in recommender systems.</i>

 * **[Install](#Install)**
 * **[TF-IDF](#TF-IDF)**
 * **[BM25](#BM25)**
 * **[Benchmarks](#Benchmarks)**
 * **[Changelog](#Changelog)**
 * **[Contributing](#Contributing)**
 * **[License](#License)**

<a name="Install"></a>
## Install 
- `npm i recommender-system`

## Examples 

<a name="TF-IDF"></a>
#### 1. TF-IDF ([Wiki](https://en.wikipedia.org/wiki/Tf%E2%80%93idf#Example_of_tf%E2%80%93idf))
Input files:
[documents.txt](https://github.com/D-Andreev/recommender-system/blob/master/test/documents.txt)
[terms.txt](https://github.com/D-Andreev/recommender-system/blob/master/test/terms.txt)
```js
    const RecommenderSystem = require('recommender-system');
    const assert = require('assert');

    const instance = new RecommenderSystem();
    instance.tfIdf('./documents.txt', './terms.txt', (err, res) => {
        assert.deepEqual(res, [0, 0.12901285528456335]);
    });
```
Run example [here](https://github.com/D-Andreev/recommender-system/blob/master/test/index.js)

<a name="BM25"></a>
#### 2. BM25 ([Wiki](https://en.wikipedia.org/wiki/Okapi_BM25))
Input files:
[documents.txt](https://github.com/D-Andreev/recommender-system/blob/master/test/documents.txt)
[terms.txt](https://github.com/D-Andreev/recommender-system/blob/master/test/terms.txt)
```js
    const RecommenderSystem = require('recommender-system');
    const assert = require('assert');

    const instance = new RecommenderSystem();
    instance.bm25('./documents.txt', './terms.txt', (err, res) => {
        assert.deepEqual(res, [0, 0.07811157572119272]);
    });
```
Run example [here](https://github.com/D-Andreev/recommender-system/blob/master/test/index.js)

<a name="Benchmarks"></a>
## Benchmarks
`npm run benchmarks`

| Implementation   | Execution time   |
| ---------------- | ---------------- |
| vanillaJS*1000   | 5.063s           |
| nativeAddon*1000 | <b>767.641ms</b> |
| vanillaJS*1000   | 5.069s           |
| nativeAddon*1000 | <b>738.792ms</b> |

<a name="Contributing"></a>
### Contributing
Pull requests are welcome.

<a name="Changelog"></a>
### Changelog
For complete changelog [click here](https://github.com/D-Andreev/recommender-system/blob/master/CHANGELOG.md).

<a name="License"></a>
### License
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
