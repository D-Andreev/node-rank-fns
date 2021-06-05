"use strict";
const addon = require('../build/Release/node-rank-fns');
class NodeRankFns {
    constructor() {
        this._addonInstance = new addon.NodeRankFns();
    }
    tfIdf(documents, terms, callback) {
        return this._addonInstance.tfIdf(documents, terms, callback);
    }
    bm25(documents, terms, callback) {
        return this._addonInstance.bm25(documents, terms, callback);
    }
}
module.exports = NodeRankFns;
