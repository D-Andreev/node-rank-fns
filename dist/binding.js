"use strict";
const addon = require('../build/Release/recommender-system');
class RecommenderSystem {
    constructor() {
        this._addonInstance = new addon.RecommenderSystem();
    }
    tfIdf(documents, terms, callback) {
        return this._addonInstance.tfIdf(documents, terms, callback);
    }
    bm25(documents, terms, callback) {
        return this._addonInstance.bm25(documents, terms, callback);
    }
}
module.exports = RecommenderSystem;
