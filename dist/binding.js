"use strict";
const addon = require('../build/Release/node-rank-fns');
class NodeRankFns {
    constructor() {
        this._addonInstance = new addon.NodeRankFns();
    }
    tfIdf(documents, terms) {
        return this._addonInstance.tfIdf(documents, terms);
    }
}
module.exports = NodeRankFns;
