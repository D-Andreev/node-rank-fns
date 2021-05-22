"use strict";
const addon = require('../build/Release/node-rank-fns-native');
;
class NodeRankFns {
    constructor(name) {
        this._addonInstance = new addon.NodeRankFns(name);
    }
    greet(strName) {
        return this._addonInstance.greet(strName);
    }
}
module.exports = NodeRankFns;
